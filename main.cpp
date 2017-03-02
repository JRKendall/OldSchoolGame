#include <array>
#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <string>
#include <queue>
#include <functional>
#include <algorithm>
#include <typeinfo>

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

vector<vector<int>> updatePlayer(int dx, int dy, vector<vector<int>> world = world){
	world[playerLocation[0]][playerLocation[1]] = 0;
	playerLocation[0] += dx;
	playerLocation[1] += dy;
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
	return updatePlayer(0, 0, updateEnemies(1, world));
}

string printWorld(){;
	string line = "|"+string(world[0].size()*2-1, '-')+"|\n|";
	string out;
	for(auto i : world){
		out += line;
		for(auto j : i){
			out += to_string(j)+"|";
		}
		out += "\n";
	}
	return out;
}

int playerAttack(int dx, int dy){
	vector<int> el = {playerLocation[0]+dx, playerLocation[1]+dy};
	int mapnum = world[el[0]][el[1]];
	if(mapnum < 3){
		return 0;
	}
	else if(mapnum == 3){
		return 0; //shop.something method goes here - interacting with shop
	}
	else{
		int ei = find(enemyLocList.begin(), enemyLocList.end(), el) - enemyLocList.begin();
		enemyStatList[ei]['H'] -= playerStatList['A'] - enemyStatList[ei]['D'];
	}
}

void enemyAttack(int ref){
	playerStatList['H'] -= enemyStatList[ref]['A'] - playerStatList['D'];
};

void enemyDie(int ref){
	removeList.emplace_back(enemyLocList[ref]);
	enemyTypeList.erase(enemyTypeList.begin()+ref);
	enemyStatList.erase(enemyStatList.begin()+ref);
	enemyLocList.erase(enemyLocList.begin()+ref);
	updateEnemies(0);
	//drop_gold(self.golddropped) // Runs the unction that causes enemies to drop gold

}

int main(){
	world = createWorld(10, 10, {{4,4,5},{6,3,5}});
	return 0;
}