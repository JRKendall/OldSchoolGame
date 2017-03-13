#define _USE_MATH_DEFINES

#include <math.h>
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
	//Gets the stats of the player from the database to be used in the game
	map<char, int> stats;
	stats['H'] = 100; //HP
	stats['A'] = 30; //Attack
	stats['D'] = 10; //Defence
	stats['G'] = 20; //Gold
	return stats;
}

vector<vector<int>> updatePlayer(int dx, int dy, vector<vector<int>> world = world, bool initial = false){
	if(playerLocation.at(0)+dx == world.size() || playerLocation.at(0)+dx < 0 ||
	playerLocation.at(1)+dy == world[0].size() || playerLocation.at(1)+dy < 0){
		return world;
	}
	world.at(playerLocation.at(0)).at(playerLocation.at(1)) = -1;
	if(world.at(playerLocation.at(0)+dx).at(playerLocation.at(1)+dy) == -1 || initial){
		playerLocation.at(0) += dx;
		playerLocation.at(1) += dy;
	}
	world.at(playerLocation.at(0)).at(playerLocation.at(1)) = -2;
	return world;
}

vector<vector<int>> updateEnemies(int setting, vector<vector<int>> world = world){
	if(setting > 0){
		for(int i = 0; i < enemyLocList.size(); i++){
			world.at(enemyLocList.at(i).at(0)).at(enemyLocList.at(i).at(1)) = i;
		};
		setting -= 1;
	}
	if(setting <= 0){
		for(auto i : removeList){
			world.at(i.at(0)).at(i.at(1)) = -1;
		};
	}
	return world;
}

void buildLists(vector<vector<int>> callingList){ //finds the list which contains the stats for the enemies found inthe relational database
	playerStatList = setStats(0);
	for(auto i : callingList){
		enemyTypeList.emplace_back(i.at(0));
		vector<int> coords = {i.at(1),i.at(2)};
		enemyLocList.emplace_back(coords);
		enemyStatList.emplace_back(setStats(i.at(0)));
	};
}

vector<vector<int>> createWorld(int width, int height, vector<vector<int>> callingList) { //creates the map for the game
	vector<vector<int>> world;
	for(int i=0; i < height; i++){
		vector<int> layer;
		for(int j=0; j < width; j++){
			layer.push_back(-1);
		};
		world.push_back(layer);
	};
	buildLists(callingList);
	return updatePlayer(0, 0, updateEnemies(1, world), true);
}

void printWorld(){; //shows the created map and assigns all of the entities to different characthers.
	map<int, string> characters;
	characters[-4] = " ";
	characters[-3] = "S";
	characters[-2] = "^";
	characters[-1] = ".";
	string line = " "+string(world.at(0).size()*2-1, ' ')+" \n ";
	string out;
	for(auto i : world){
		attron(COLOR_PAIR(1));
		addstr(line.c_str());
		attroff(COLOR_PAIR(1));
		for(auto j : i){
			string jstring;
			if(j >= 0){
				attron(COLOR_PAIR(5));
				jstring = to_string(enemyTypeList[j])+" ";
			}
			else{
				attron(COLOR_PAIR(-j));
				jstring = characters[j]+" ";
			}
			addstr(jstring.c_str());
			attroff(COLOR_PAIR(-j));
		}
		addstr("\n");
	}
	//return out.c_str();
}

void enemyDie(int ref, vector<vector<int>> enemyLocList, vector<int> enemyTypeList, vector<map<char, int>> enemyStatList){ //The function which handles the enemy dying. Reponsible for removing enemies from the database and the game
	removeList.emplace_back(enemyLocList.at(ref));
	enemyTypeList.erase(enemyTypeList.begin()+ref);
	enemyStatList.erase(enemyStatList.begin()+ref);
	enemyLocList.erase(enemyLocList.begin()+ref);
	world = updateEnemies(0, world);
	//drop_gold(self.golddropped) // Runs the unction that causes enemies to drop gold

}

void playerAttack(int dx, int dy){ //Handles the player attacking. If used on an enemy depletes their health. If used on a shop, acesses the shop screen
	int mapnum = world.at(playerLocation.at(0)+dx).at(playerLocation.at(1)+dy);
	if(mapnum < 0){
		return;
	}
	else if(mapnum == -3){
		return; //shop.something method goes here - interacting with shop
	}
	else{
		enemyStatList.at(mapnum)['H'] -= playerStatList['A'] - enemyStatList.at(mapnum)['D'];
		if(enemyStatList.at(mapnum)['H'] <= 0){
			enemyDie(mapnum, enemyLocList, enemyTypeList, enemyStatList);
		}
	}
}

bool enemyAttack(){ //run when an enemy attacks the player. Takes points from the player's health depending on how much attack the enemy has and the player's defence
	int j;
	for(int i = 0; i < 4; i+=1){
		j = i*M_PI/2;
		if(playerLocation[0]+sin(j) == world.size() || playerLocation[0]+sin(j) < 0 ||
		playerLocation[1]+(cos(j)*-1) == world[0].size() || playerLocation[1]+(cos(j)*-1) < 0){
			break;
		}
		j = world[playerLocation[0]+sin(j)][playerLocation[1]+(cos(j)*-1)];
		if(j >= 0){
			playerStatList['H'] -= enemyStatList.at(j)['A'] - playerStatList['D'];;
		}
	}
	if(playerStatList['H'] <= 0){
		return true;
	}
	return false;
};

vector<vector<int>> addObs(int t, int b, int l, int r, vector<vector<int>> world){
	for(int i = t; i < b; i++){
		for(int j = l; j < r; j++){
			world[i][j] = -4;
		}
	}
	return world;
}

void gameLoop(){ //Handles the running of the game and also assigns the player functions to different keys
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
	start_color();
	init_color(COLOR_YELLOW, 953, 612, 71);
	init_color(COLOR_MAGENTA, 827, 329, 0);
	init_pair(1, COLOR_GREEN, COLOR_YELLOW);
	init_pair(2, COLOR_BLACK, COLOR_YELLOW);
	init_pair(3, COLOR_BLACK, COLOR_YELLOW);
	init_pair(4, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(5, COLOR_RED, COLOR_YELLOW);
	printWorld();
	refresh();
	for(int i = 0; i > -1; i++){
		key = getch();
		if(movingKeys.find(key) != movingKeys.end()){
			args = movingKeys[key];
			world = updatePlayer(args.at(0),args.at(1),world);
		}
		else if(attackKeys.find(key) != attackKeys.end()){
			args = attackKeys[key];
			playerAttack(args.at(0),args.at(1));
		}
		if(enemyAttack() || key == 96){
			break;
		}
		clear();
		printWorld();
		addstr(to_string(i).c_str());
		refresh();
	}
	clear();
	addstr("Game Over!");
	refresh();
	getch();
	endwin();
}

int main(){
	world = createWorld(20, 20, {{4,4,5},{6,3,5}});
	world = addObs(14,20,15,20,world);
	gameLoop();

	return 0;
}
