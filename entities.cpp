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
	int self.HP = HP;
        int self.damage = damage;
        int self.defence = defence;
        int self.x = x;
        int self.y = y;

int setlocation(self ,x ,y)
	{
	 int self.location = x;
	 int self.location = y;
	}
}



class Enemy(Entity):
{
	 public:
	 int self.HP = HP;
 	 int self.attack = attack;
	 int self.defence = defence;
	 int self.golddropped = golddropped;
	 int self.ref = ref;
	 

int die(self, map)
	{
	 map.removelist.emplace_back(map.enemyList.pop(self.ref))[1]; //  Ads the second element of the nested enemy vector, and appends it to map.removeList.
	 for ( int i; i < map.enemyList.size; map.enemyList[i][2].ref = i ) // Bad solution. May be replaced later
		{
		 
 		}
	map.updateEnemies(0)
	self.drop_gold(self.golddropped) // Runs the unction that causes enemies to drop gold

	 return 0;
	}
//enemy.drop_gold
int drop_gold(self, golddropped)
	{
	//when enemy dies a amount of gold will be dropped depending on the type of enemy
	return 0;
	}

//enemy.attack
int attack(self)
	{
	 player.HP -= self.damage - player.defence;
	return 0;
	}
}
