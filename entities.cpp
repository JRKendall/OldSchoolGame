// enemy.die may need changes
#include <array>
#include <vector>
#include <iostream>
#include <queue>
#include <functional>
using namespace std;

int main()
	{
	 return 0;
	}

class Entity():
{
	public:
		int self.HP;
        	int self.attack;
        	int self.defence;
        	int self.x;
        	int self.y;

void setlocation(self ,x ,y)
	{
	 int self.location = x;
	 int self.location = y;
	}
}

class Player(Entity):
{
	public:
		int self.x;
		int self.y;
int attack(self, map, dx, dy)
	{
	 int el = (self.x+dx, self.y+dy);
	 int mapnum = map.map[el[0]][el[1]];
	 
	if (mapnum < 3)
		{
		 return 0;
		}
	else if (mapnum == 3)
		{
		 return 0; //shop.something method goes here - interacting with shop
		}
	else
		{
		 // Need help with converting the below for loop into c++
			for i in map.enemyList:
                if i[1] == el:
                    i[2].HP -= (self.damage - i[2].defence)
        #else Index map.enemyList if map.enemyList[i][1] == tuple then health is map.enemyList[i][2].HP
        #Modify it by self.attack - map.enemyList[i][2].defence
		}

class Enemy(Entity):
{
	 public:
	 	int self.HP;
 	 	int self.attack;
	 	int self.defence;
	 	int self.golddropped;
	 	int self.ref;
	 

void die(self, map)
	{
	 map.removelist.emplace_back(map.enemyList.pop(self.ref))[1]; //  Ads the second element of the nested enemy vector, and appends it to map.removeList.
	 for ( int i; i < map.enemyList.size; map.enemyList[i][2].ref = i ) // Bad solution. May be replaced later
		{
		 
 		}
	map.updateEnemies(0)
	self.drop_gold(self.golddropped) // Runs the unction that causes enemies to drop gold

	}
//enemy.drop_gold
int drop_gold(self, golddropped)
	{
	//when enemy dies a amount of gold will be dropped depending on the type of enemy
	return 0;
	}

//enemy.attack
void attack(self)
	{
	 player.HP -= self.damage - player.defence;
	}
}
