from Ai import Tile
from Ai import PathFinding
from Enum.Direction import *
from time import *


class Target(Enum):
    NOTHING = 0
    FOOD = 1
    STONE = 2
    PLAYER = 3


class Ai:

    def __init__(self, x, y):
        self.__inventory = {"food": 10, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0,
                            "thystame": 0}
        self.__map = [[Tile.Tile() for _ in range(x)] for _ in range(y)]
        self.__coord = [0, 0]
        self.dir = Direction.SOUTH
        self.__pathFind = PathFinding.PathFinding(x, y)
        self.__level = 1

        self.elevation_array = {1: ["linemate"],
                                2: ["linemate", "deraumere", "sibur"],
                                3: ["linemate", "sibur", "phiras"],
                                4: ["linemate", "deraumere", "sibur", "phiras"],
                                5: ["linemate", "deraumere", "sibur", "mendiane"],
                                6: ["linemate", "deraumere", "sibur", "phiras"],
                                7: ["linemate", "deraumere", "sibur", "mendiane", "phyras", "thystame"]}

        self.egg = False

    def think(self):
        toto, self.dir = self.__pathFind.goToTile(self.__coord, (1, 1), self.dir)
        print(self.dir)
        print(toto)
        print(self.__coord)
        toto, self.dir = self.__pathFind.goToTile(self.__coord, (2, 2), self.dir)
        print(self.dir)
        print(toto)

    def getMap(self):
        return self.__map

    def getCoord(self) -> list:
        return self.__coord

    def getInventory(self):
        return self.__inventory

    def getDir(self):
        return self.dir

    def getLevel(self):
        return self.__level

    def setCoord(self, x: int, y: int):
        self.__coord[0] = x
        self.__coord[1] = y

    def levelUp(self):
        self.__level += 1
