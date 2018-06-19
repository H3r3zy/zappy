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

        self.elevation_array = {1: [("linemate", 1)],
                                2: [("linemate", 1), ("deraumere", 1), ("sibur", 1)],
                                3: [("linemate", 2), ("sibur", 1), ("phiras", 2)],
                                4: [("linemate", 1), ("deraumere", 1), ("sibur", 2), ("phiras", 1)],
                                5: [("linemate", 1), ("deraumere", 2), ("sibur", 1), ("mendiane", 3)],
                                6: [("linemate", 1), ("deraumere", 2), ("sibur", 3), ("phiras", 1)],
                                7: [("linemate", 2), ("deraumere", 2), ("sibur", 2), ("mendiane", 2), ("phyras", 2),
                                    ("thystame", 1)]}
        self.elevation_player = [0, 1, 2, 2, 4, 4, 6, 6]
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
