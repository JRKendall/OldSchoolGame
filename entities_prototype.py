from map import *

class Entity():
    """"This is the class for all entities within the game"""
    
    def __init__(self, HP, attack, defence, x, y):
        self.HP = HP
        self.damage = damage
        self.defence = defence
        self.x = x
        self.y = y

    def setlocation(self,x,y):
        """Sets the location of the entity on the map"""
        self.locationx = x
        self.locationy = y

    def die(self):
        """A method that is run when the HP of the entity reaches 0"""
        #May behave differently for Players and Enemies
        pass

class Player(Entity):

    def __init__(self, x, y):
        self.HP = 100
        self.damage = 20
        self.defence = 20
        self.x = x
        self.y = y

    def move(self, map, dx, dy):
        self.map.playerLocation[0] += dx
        self.map.playerLocation[1] += dy
        self.map.updatePlayer()

    def attack(self, map, dx, dy):
        #Make tuple of enemy's location based on dx,dy,player.x and player.y
        el = (self.x+dx, self.y+dy)
        #Store numbercode of area at tuple coords (map.map[tuple[0]][tuple[1]])
        mapnum  = map.map[el[0]][el[1]]
        #Conditional to check area contains enemy if < 3 then return
        if mapnum < 3:
            return
        elif mapnum == 3:
            #shop.something()
            return
        else:
            for i in map.enemyList:
                if i[1] == el:
                    i[2].HP -= (self.damage - i[2].defence)
        #else Index map.enemyList if map.enemyList[i][1] == tuple then health is map.enemyList[i][2].HP
        #Modify it by self.attack - map.enemyList[i][2].defence
            """Run when one entity attacks another. (HP lost = Attackers attack - defenders defence)"""

class Enemy(Entity):

    def __init__(self, HP, attack, defence, golddropped, ref):
        self.HP = HP
        self.damage = attack
        self.defence = defence
        self.golddropped = golddropped
        self.ref = ref

    def die(self,map):
        map.removeList.append(map.enemyList.pop(self.ref)[1])
        for i in range(len(map.enemyList)):
                map.enemyList[i][2].ref = i
                #Above is a bad solution, should be replaced but may need fundamental change
        map.updateEnemies()
        self.drop_gold(self.golddropped)

    def drop_gold(self, golddropped):
        #Would give the player gold upon death. Amount depends on enemy type.
        pass

    def attack(self):
        player.HP -= (self.damage - player.defence)

    
