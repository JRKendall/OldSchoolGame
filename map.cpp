#include <vector>
#include "entities.cpp"
using namespace std;

int main(){
	return 0;
}

class map{	

	int updateEnemies(self, setting = 1){
		if(setting > 0)
			for(int i : self.enemyList){
				int self.map[i[1][0]][i[1][1]] = i[0]
			}
			setting = setting - 1
		if(setting <= 0)
			for(int i : self.removeList){
				int self.map[i[0]][i[1]] = 0
			}
	}
	
	public:
		int width;
		int height;
		vector<list> removeList;
		list<int> playerLocation;
		Player player
		player.x = playerLocation[0]
		player.y = playerLocation[1]
		self.updatePlayer()
		self.updateEnemies()
		self.createEnemy()
}