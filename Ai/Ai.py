from enum import Enum
from Ai import Tile
from Ai import PathFinding


class Target(Enum):
    NOTHING = 0
    FOOD = 1
    STONE = 2
    PLAYER = 3


class Direction(Enum):
    NORTH = 0
    SOUTH = 1
    EAST = 2
    WEST = 3


class Ai:

    def __init__(self, x, y):
        self.__inventory = {"food": 10, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0,
                            "thystame": 0}
        self.__map = [[Tile.Tile() for _ in range(x)] for _ in range(y)]
        self.__coord = (9, 0)
        self.__dir = Direction.SOUTH

    def think(self):
        for key in self.__inventory:
            print("Key : %s --> value %d" % (key, self.__inventory[key]))
        print(self.__inventory)
        toto = PathFinding.PathFinding()

        toto.goToTile(self.__coord, [8, 0])

    def getMap(self):
        return self.__map

    def getCoord(self) -> tuple:
        return self.__coord

    def getInventory(self):
        return self.__inventory

    def getDir(self):
        return self.__dir