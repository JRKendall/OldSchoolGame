#include <array>
#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <string>
#include <queue>
#include <functional>
#include <algorithm>
#include <ncurses.h>

using namespace std;

vector<vector<int>> removeList;
vector<int> playerLocation = {5,5};
vector<vector<int>> enemyLocList;
vector<int> enemyTypeList;
vector<map<char, int>> enemyStatList;
map<char, int> playerStatList;
vector<vector<int>> world;

map<char, int> setStats(int ref){
	//Lookup stats in stat lists, for now defaults used
	map<char, int> stats;
	stats['H'] = 100; //HP
	stats['A'] = 30; //Attack
	stats['D'] = 10; //Defence
	stats['G'] = 20; //Gold
	return stats;
}

vector<vector<int>> updatePlayer(int dx, int dy, vector<vector<int>> world = world, bool initial = false){
	world[playerLocation[0]][playerLocation[1]] = 0;
	if(world[playerLocation[0]+dx][playerLocation[1]+dy] == 0 || initial){
		playerLocation[0] += dx;
		playerLocation[1] += dy;
	}
	world[playerLocation[0]][playerLocation[1]] = 1;
	return world;
}

vector<vector<int>> updateEnemies(int setting, vector<vector<int>> world = world){
	if(setting > 0){
		for(int i = 0; i < enemyLocList.size(); i++){
			world[enemyLocList[i][0]][enemyLocList[i][1]] = enemyTypeList[i];
		};
		setting -= 1;
	}
	if(setting <= 0){
		for(auto i : removeList){
			world[i[0]][i[1]] = 0;
		};
	}
	return world;
}

void buildLists(vector<vector<int>> callingList){
	playerStatList = setStats(1);
	for(auto i : callingList){
		enemyTypeList.emplace_back(i[0]);
		vector<int> coords = {i[1],i[2]};
		enemyLocList.emplace_back(coords);
		enemyStatList.emplace_back(setStats(i[0]));
	};
}

vector<vector<int>> createWorld(int width, int height, vector<vector<int>> callingList) {
	vector<vector<int>> world;
	for(int i=0; i < height; i++){
		vector<int> layer;
		for(int j=0; j < width; j++){
			layer.push_back(0);
		};
		world.push_back(layer);
	};
	buildLists(callingList);
	return updatePlayer(0, 0, updateEnemies(1, world), true);
}

const char* printWorld(){;
	string line = " "+string(world[0].size()*2-1, ' ')+" \n ";
	string out;
	for(auto i : world){
		out += line;
		for(auto j : i){
			out += to_string(j)+" ";
		}
		out += "\n";
	}
	return out.c_str();
}

void enemyDie(int ref){
	removeList.emplace_back(enemyLocList[ref]);
	enemyTypeList.erase(enemyTypeList.begin()+ref);
	enemyStatList.erase(enemyStatList.begin()+ref);
	enemyLocList.erase(enemyLocList.begin()+ref);
	world = updateEnemies(0, world);
	//drop_gold(self.golddropped) // Runs the unction that causes enemies to drop gold

}

void playerAttack(int dx, int dy){
	vector<int> el = {playerLocation[0]+dx, playerLocation[1]+dy};
	int mapnum = world[el[0]][el[1]];
	if(mapnum < 3){
		return;
	}
	else if(mapnum == 3){
		return; //shop.something method goes here - interacting with shop
	}
	else{
		int ei = find(enemyLocList.begin(), enemyLocList.end(), el) - enemyLocList.begin();
		enemyStatList[ei]['H'] -= playerStatList['A'] - enemyStatList[ei]['D'];
		//cout << "This";
		if(enemyStatList[ei]['H'] <= 0){
			enemyDie(ei);
		}
	}
}

void enemyAttack(int ref){
	playerStatList['H'] -= enemyStatList[ref]['A'] - playerStatList['D'];
};

void gameLoop(){
	int key;
	int keyIndex;
	vector<int> args;
	map<int, vector<int>> movingKeys;
	movingKeys[97] = {0,-1};
	movingKeys[100] = {0,1};
	movingKeys[115] = {1,0};
	movingKeys[119] = {-1,0};
	map<int, vector<int>> attackKeys;
	attackKeys[49] = {0,-1}; //Left
	attackKeys[50] = {1,0}; //Down
	attackKeys[51] = {0,1}; //Right
	attackKeys[53] = {-1,0}; //Up
	initscr();
	addstr(printWorld());
	refresh();
	int i = 0;
	while(key != 96){
		key = getch();
		if(movingKeys.find(key) != movingKeys.end()){
			args = movingKeys[key];
			world = updatePlayer(args[0],args[1],world);
		}
		else if(attackKeys.find(key) != attackKeys.end()){
			args = attackKeys[key];
			playerAttack(args[0],args[1]);
			getch();
		}
		for(int i = 0 float j = 0; i < 2; i++ j+=0.5){
			
		clear();
		addstr(printWorld());
		refresh();
	}
	endwin();
}

int main(){
	world = createWorld(10, 10, {{4,4,5},{6,3,5}});
	gameLoop();
	
	return 0;
}