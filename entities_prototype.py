class Entity():
    """"This is the class for all entities within the game"""
    
    def __init__(self, HP, attack, defence):
        self.HP = HP
        self.attack = attack
        self.defence = defence
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
        """Moves the player by one tile when a button is pressed"""
        #I don't know how we are handling movement yet
        pass

class Enemy(Entity):

    def __init__(self, HP, attack, defence, golddropped):
        self.golddropped = golddropped

    def die(self):
        self.drop_gold

    def drop_gold(self, golddropped):
        #Would give the player gold upon death. Amount depends on enemy type.
        pass
    
    
    
    
