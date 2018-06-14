from Ai import Tile
from Ai import PathFinding
from Enum.Direction import *


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
        self.__dir = Direction.SOUTH
        self.__pathFind = PathFinding.PathFinding(x, y)
        self.__level = 1

    def think(self):
        self.__pathFind.goToTile(self.__coord, (3, 0), self.__dir)

    def getMap(self):
        return self.__map

    def getCoord(self) -> list:
        return self.__coord

    def getInventory(self):
        return self.__inventory

    def getDir(self):
        return self.__dir

    def getLevel(self):
        return self.__level