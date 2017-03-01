#include <vector>
#include <list>
#include <iostream>
#include "entities.cpp"

using namespace std;


class Map{	

public:

	vector<vector<int>> map;
	vector<vector<int>> removeList;
	list<int> playerLocation[2];
	vector<vector<int>> enemyLocList;
	vector<int> enemyTypeList;
	int width;
	int height;
	
	Map(int width, int height, vector<vector<int>> callingList) {
		this->width = width;
		for(int i=0; i < height; i++){
			vector<int> layer;
			for(int j=0; j < width; j++){
				layer.push_back(0);
			};
			this->map.push_back(layer);
		};
		for(auto i : callingList){
			this->enemyTypeList.push_back(i[0]);
			this->enemyLocList.push_back({i[1],i[2]});
		};
		//vector<Enemy> enemyList = {};
		//this->updatePlayer();
		//this->updateEnemies();
		//this->createEnemy();
		//Player player(playerLocation[0], playerLocation[1]);
	};
	
	int updateEnemies(int setting = 1){
		if(setting > 0)
			for(int i = 0; i < this->enemyLocList.size(); i++){
				vector<int> j = this->enemyLocList[i];
				this->map[j[0]][j[1]] = this->enemyTypeList[i];
			};
			setting = setting - 1;
		if(setting <= 0)
			for(auto i : this->removeList){
				this->map[i[0]][i[1]] = 0;
			};
	};
};

int main(){
	//Map map(10,10,{{1,2,3},{4,4,5}});
	return 0;
}