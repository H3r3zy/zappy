from Ai_Client.Ai import Tile
from Ai_Client.Ai import PathFinding
from Ai_Client.Enum.Direction import *
import os, random


class Ai:

    def __init__(self, x, y):
        self.__mapSize = (x, y)
        self.__inventory = {"food": 10, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0,
                            "thystame": 0}
        self.__map = [[Tile.Tile() for _ in range(x)] for _ in range(y)]
        self.__coord = [0, 0]
        self.dir = Direction.SOUTH
        self.__pathFind = PathFinding.PathFinding(x, y)
        self.__level = 1
        self.__id = os.getpid() * random.randint(1, 3000)

        self.elevation_array = {1: [("linemate", 1)],
                                2: [("linemate", 1), ("deraumere", 1), ("sibur", 1)],
                                3: [("linemate", 2), ("sibur", 1), ("phiras", 2)],
                                4: [("linemate", 1), ("deraumere", 1), ("sibur", 2), ("phiras", 1)],
                                5: [("linemate", 1), ("deraumere", 2), ("sibur", 1), ("mendiane", 3)],
                                6: [("linemate", 1), ("deraumere", 2), ("sibur", 3), ("phiras", 1)],
                                7: [("linemate", 2), ("deraumere", 2), ("sibur", 2), ("mendiane", 2), ("phyras", 2),
                                    ("thystame", 1)]}
        self.elevation_player = [0, 1, 2, 2, 4, 4, 6, 6]
        self.__Broadcaster = False
        self.__listenDir = {
            Direction.NORTH: [(0, -1), (-1, -1), (-1, 0), (-1, 1), (0, 1), (1, 1), (1, 0), (1, -1)],
            Direction.SOUTH: [(0, 1), (1, 1), (1, 0), (1, -1), (0, -1), (-1, -1), (-1, 0), (-1, 1)],
            Direction.EAST: [(1, 0), (1, -1), (0, -1), (-1, -1), (-1, 0), (-1, 1), (0, 1), (1, 1)],
            Direction.WEST: [(-1, 0), (-1, 1), (0, 1), (1, 1), (1, 0), (1, -1), (0, -1), (-1, -1)]
        }

    def getMap(self):
        return self.__map

    def getCoord(self) -> list:
        coord = []
        coord.append(self.__coord[0] % \
                     self.__mapSize[0])
        coord.append(self.__coord[1] % \
                     self.__mapSize[1])
        return coord

    def getInventory(self):
        return self.__inventory

    def getDir(self) -> Direction:
        return self.dir

    def getLevel(self):
        return self.__level

    def setCoord(self, x: int, y: int):
        self.__coord[0] = x
        self.__coord[1] = y

    def levelUp(self, lvl: int):
        self.__level = lvl

    def getBroadcaster(self):
        return self.__Broadcaster

    def setBroadcaster(self, b: bool):
        self.__Broadcaster = b

    def WhereIs(self, number: int) -> list:
        toto = self.__listenDir[self.dir]
        coord = toto[int(number) - 1]
        player_coord = [self.__coord[0] + coord[0], self.__coord[1] + coord[1]]
        if player_coord[0] < 0:
            player_coord[0] = self.__mapSize[0] - 1
        elif player_coord[0] > self.__mapSize[0]:
            player_coord[0] = 0

        if player_coord[1] < 0:
            player_coord[1] = self.__mapSize[1] - 1
        elif player_coord[1] > self.__mapSize[1]:
            player_coord[1] = 0
        return player_coord

    def getId(self) -> int:
        return self.__id
