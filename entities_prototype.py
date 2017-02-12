from map import *

class Entity():
    """"This is the class for all entities within the game"""
    
    def __init__(self, HP, attack, defence, x, y):
        self.HP = HP
        self.attack = attack
        self.defence = defence
        self.x = x
        self.y = y
        if HP == 0:
            self.die

    def setlocation(self,x,y):
        """Sets the location of the entity on the map"""
        self.locationx = x
        self.locationy = y

    def die(self):
        """A method that is run when the HP of the entity reaches 0"""
        #May behave differently for Players and Enemies
        pass

    def attack(self, target):
            """Run when one entity attacks another. (HP lost = Attackers attack - defenders defence)"""
            pass

class Player(Entity):

    def __init__(self, HP, attack, defence):
        Player.__init__(self, 100, 20, 20)

    def move(self, dx, dy):
        map.playerLocation[0] += dx
        map.playerLocation[1] += dy
        map.updatePlayer()

class Enemy(Entity):

    def __init__(self, HP, attack, defence, golddropped, ref):
        self.golddropped = golddropped
        self.ref = ref

    def die(self,map):
        map.removeList.append(map.enemyList.pop(self.ref)[1:3])
        for i in range(len(map.enemyList)):
                map.enemyList[i][3].ref = i
                #Above is a bad solution, should be replaced but may need fundamental change
        map.updateEnemies()
        self.drop_gold(self.golddropped)

    def drop_gold(self, golddropped):
        #Would give the player gold upon death. Amount depends on enemy type.
        pass

    
