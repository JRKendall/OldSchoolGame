class Map():
	#Within the map, 0 signifies free space, 1 signifies the player, 2 signifies an obsticle, 3 signifies the shop and anything greater refers to a type of enemy	

	#Add the positions of the stored entities to the map
	def update(self):
		#self.map[self.playerLocation[0]][self.playerLocation[1]] = 0
		#self.map[player.x][player.y] = 1
		#self.playerLocation = (player.x, player.y)
		for i in self.enemyList:
			self.map[i[1]][i[2]] = i[0]

	#Create the map
	def __init__(self,height, width, playerLocation, enemyList):
		self.map = [[0 for i in range(width)] for i in range(height)]
		self.width = width
		self.enemyList = enemyList
		self.playerLocation = playerLocation
		#player = Player(playerLocation)
		self.update()
	
	#Displays the map as a str
	def __str__(self):
		outstr = '--'*self.width+'-\n'
		for i in self.map:
			outstr += '|'
			for j in i:
				outstr += str(j) + '|'
			outstr += '\n'+'--'*self.width+'-\n'
		return outstr

#Example
map = Map(10,10,(3,2),[[4,3,5],[6,4,7]])
print(map)