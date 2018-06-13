#!/usr/bin/env python
# coding: utf-8

import re
from Client import Client
from Ai.Ai import *
from collections import deque

class CmdParser:
    def __init__(self, player: Ai, queue: deque):
        self.__player = player
        self.__map = player.getMap()
        self.__inv = player.getInventory()
        self.__queue = queue
        self.__patterns = {
            'Look': re.compile("\[( \w+)*(,( \w+)*)* \]", re.ASCII),
            'Inventory': re.compile("\[(( \w+ \d+)(,( \w+ \d+)*)* )?\]", re.ASCII),
            'Connect_nbr': re.compile("%d+", re.ASCII),
            'Incantation': re.compile("(Elevation underway Current level: \d)|(ko)", re.ASCII),
            'Forward': re.compile("ok", re.ASCII),
            'Right': re.compile("ok", re.ASCII),
            'Left': re.compile("ok", re.ASCII),
            'Broadcast': re.compile("ok", re.ASCII),
            'Fork': re.compile("ok", re.ASCII),
            'Eject': re.compile("(ok)(ko)", re.ASCII),
            'Take': re.compile("(ok)|(ko)", re.ASCII),
            'Set': re.compile("(ok)|(ko)", re.ASCII)
        }
        self.__dirs = {
            Direction.SOUTH: CmdParser.viewSouth,
            Direction.NORTH: CmdParser.viewNorth,
            Direction.EAST: CmdParser.viewEast,
            Direction.WEST: CmdParser.viewWest,
        }

    @staticmethod
    def viewSouth(x, y, end) -> tuple:
        for ny in range(y, y + end + 1):
            level = ny - y
            for nx in range(x - level, x + level + 1):
                yield (nx, ny)

    @staticmethod
    def viewNorth(x, y, end) -> tuple:
        for ny in range(y, y - end - 1, - 1):
            level = y - ny
            for nx in range(x - level, x + level + 1):
                yield (nx, ny)

    @staticmethod
    def viewEast(x, y, end) -> tuple:
        for nx in range(x, x + end + 1):
            level = nx - x
            for ny in range(y - level, y + level + 1):
                yield (nx, ny)

    @staticmethod
    def viewWest(x, y, end) -> tuple:
        for nx in range(x, x - end - 1, - 1):
            level = x - nx
            for ny in range(y - level, y + level + 1):
                yield (nx, ny)

    def parse_map(self, map: str):
        map = map.replace("[", "").replace("]", "")
        tiles = map.split(",")
        i = 0
        for x, y in self.__dirs[self.__player.getDir()](self.__player.getCoord()[0], self.__player.getCoord()[1], 1):
            currentTile = self.__map[y][y]
            currentTile.reset()
            for elem in tiles[i].split(" "):
                if elem == "player":
                    currentTile.setPlayer(currentTile.getPlayer() + 1)
                    continue
                if len(elem) > 0:
                    currentTile.getStones()[elem] += 1
            i += 1
        for tile in tiles:
            elem = tile.split(" ")



    def parse_inv(self, inv: str):
        inv = inv.replace("[", "").replace("]", "")
        elems = inv.split(",")
        for x in range(0, len(elems)):
            elems[x] = elems[x].lstrip(" ")
            elems[x] = elems[x].rstrip(" ")
        for elem in elems:
            arr = tuple(elem.split(" ", 2))
            self.__inv[arr[0]] = int(arr[1])

    def parse(self, cmd: str) -> bool:
        if cmd == "dead":
            return False
        if self.__queue[0] in self.__patterns:
            last = self.__queue.popleft()
            match = self.__patterns[last].match(cmd)
            #print(match.group(0))
            if last == "Look":
                self.parse_map(match.group(0))
            elif last == "Inventory":
                self.parse_inv(match.group(0))
        else:
            raise Client.ZappyException('Unexpected response ' + cmd)
        return True
