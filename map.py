from entities_prototype import *

class Map():
	#Within the map, 0 signifies free space, 1 signifies the player, 2 signifies an obsticle, 3 signifies the shop and anything greater refers to a type of enemy	

	#Ensures the player is correct represented
	def updatePlayer(self):
		pass
		#self.map[self.playerLocation[0]][self.playerLocation[1]] = 0
		#self.map[player.x][player.y] = 1
		#self.playerLocation = (player.x, player.y)
	
	#Adds all living enemies to the map
	def updateEnemies(self):
		for i in self.removeList:
			self.map[i[0]][i[1]] = 0
		for i in self.enemyList:
			self.map[i[1]][i[2]] = i[0]

	#Declares one or all enemies
	def createEnemy(self, ref = 'all', x = 0, y = 0):
		if ref == 'all':
			for i in self.enemyList:
				if len(i) >= 4:
					break
				#Lookup values for each type of enemy, randoms used for now
				i.append(Enemy(20, 5, 5, 10, self.enemyList.index(i)))
		else:
			self.enemyList.append([ref,x,y,Enemy(20, 5, 5, 10, len(self.enemyList))])

	#Create the map
	def __init__(self,height, width, playerLocation, enemyList):
		self.map = [[0 for i in range(width)] for i in range(height)]
		self.width = width
		self.enemyList = enemyList
		self.removeList = []
		self.playerLocation = playerLocation
		#player = Player(playerLocation[0],playerLocation[1])
		self.updatePlayer()
		self.updateEnemies()
		self.createEnemy()
	
	#Displays the map as a str
	def __str__(self):
		outstr = '--'*self.width+'-\n'
		for i in self.map:
			outstr += '|'
			for j in i:
				outstr += str(j) + '|'
			outstr += '\n'+'--'*self.width+'-\n'
		return outstr