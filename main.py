from map import *
from entities_prototype import *

#Gameloop goes in this file
map = Map(10,10,(3,2),[[4,3,5],[6,4,7]])
map.enemyList[0][3].die(map)
print(map)