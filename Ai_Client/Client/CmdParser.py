#!/usr/bin/env python
# coding: utf-8

import re
from os import system
from sys import argv
from Ai_Client.Ai.Ai import *
from collections import deque
from Ai_Client.Enum.Direction import *


class CmdParser:
    def __init__(self, player: Ai, queue: deque, msgQueue: deque, info):
        self.__info = info
        self.__player = player
        self.__map = player.getMap()
        self.__inv = player.getInventory()
        self.__queue = queue
        self.__msgQueue = msgQueue
        self.__patterns = {
            'Look': re.compile("\[( ?\w+)*(,( \w+)*)* ?\]", re.ASCII),
            'Inventory': re.compile("\[( ?(\w+ \d+)(,( \w+ \d+)?)* ?)\]", re.ASCII),
            'Connect_nbr': re.compile("%d+", re.ASCII),
            'Incantation': re.compile("(Elevation underway)|(Current level: \d)|(ko)", re.ASCII),
            'Forward': re.compile("ok", re.ASCII),
            'Right': re.compile("ok", re.ASCII),
            'Left': re.compile("ok", re.ASCII),
            'Broadcast': re.compile("ok", re.ASCII),
            'Fork': re.compile("ok", re.ASCII),
            'Eject': re.compile("(ok)(ko)", re.ASCII),
            'Take': re.compile("(ok)|(ko)", re.ASCII),
            'Set': re.compile("(ok)|(ko)", re.ASCII)
        }
        self.__unexpected = (
            (re.compile("message (\d), (.*)", re.ASCII), self.message),
            (re.compile("Elevation underway"), self.nothing),
            (re.compile("Current level (\d)"), self.lvl_up),
            (re.compile("eject: (\d)"), self.eject)
        )
        self.__dirs = {
            Direction.SOUTH: CmdParser.viewSouth,
            Direction.NORTH: CmdParser.viewNorth,
            Direction.EAST: CmdParser.viewEast,
            Direction.WEST: CmdParser.viewWest,
        }
        self.__actions = {
            'Look': self.parse_map,
            'Inventory': self.parse_inv,
            'Fork': self.fork,
            'Take': self.take,
            'Set': self.set,
            'Incantation': self.lvl_up
        }
        self.__handledId = 0
        self.__deltas = {
            1: (0, -1),
            2: (1, -1),
            3: (1, 0),
            4: (1, 1),
            5: (0, 1),
            6: (-1, 1),
            7: (-1, 0),
            8: (-1, -1)
        }

    def nothing(self, _):
        pass

    def message(self, msg):
        match = re.match("message (\d), (.*)", msg)
        self.__msgQueue.append((match.group(1), match.group(2)))

    def lvl_up(self, ans: str, _1 = "", _2 = ""):
        match = re.search("(\d)", ans)
        if match:
            self.__player.levelUp(int(match.group(1)))

    def set(self, ans: str, obj: str, pos: tuple):
        if ans == "ok":
            self.__player.getInventory()[obj] -= 1
            self.__map[pos[1]][pos[0]].getStones()[obj] += 1
        else:
            self.__player.getInventory()[obj] = 0

    def take(self, ans: str, obj: str, pos: tuple):
        if ans == "ok":
            self.__player.getInventory()[obj] += 1
            self.__map[pos[1]][pos[0]].getStones()[obj] -= 1
        else:
            self.__map[pos[1]][pos[0]].getStones()[obj] = 0

    def fork(self):
        system(argv[0] + " -p " + str(self.__info[0]) + " -n " + self.__info[1] + " -h " + self.__info[2])

    def eject(self, ans):
        key = int(ans)
        delta = self.__deltas[key]
        pos = self.__player.getCoord()
        self.__player.setCoord(pos[0] + delta[0], pos[1] + delta[1])

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

    def parse_map(self, map: str, arg, pos):
        map = map.replace("[", "").replace("]", "")
        tiles = map.split(",")
        i = 0
        print("Je vais parse la map")
        for x, y in self.__dirs[pos[1]](pos[0][0], pos[0][1], self.__player.getLevel()):
            currentTile = self.__map[y % len(self.__player.getMap())][x % len(self.__player.getMap()[0])]
            currentTile.reset()
            for elem in tiles[i].split(" "):
                if elem == "player":
                    currentTile.setPlayer(currentTile.getPlayer() + 1)
                    continue
                if len(elem) > 0:
                    currentTile.getStones()[elem] += 1  # Changer
            i += 1

    def parse_inv(self, inv: str, _1, _2):
        inv = inv.replace("[", "").replace("]", "")
        elems = inv.split(",")
        for x in range(0, len(elems)):
            elems[x] = elems[x].lstrip(" ").rstrip(" ")
        for elem in elems:
            arr = tuple(elem.split(" ", 2))
            self.__inv[arr[0]] = int(arr[1])

    def get_last(self):
        return self.__handledId

    def parse(self, cmd: str) -> bool:
        if cmd == "dead":
            return False
        last = self.__queue.popleft()
        match = self.__patterns[last[0]].match(cmd)
        if match is None:
            for reg, func in self.__unexpected:
                if reg.match(cmd):
                    func(cmd)
                    return True
        self.__handledId += 1
        try:
            if last[0] in self.__actions.keys() and match is not None:
                self.__actions[last[0]](match.group(0), last[1], last[2])
        except AttributeError:
            if cmd == "ko":
                self.__player.egg = True
            else:
                print("Could not link '" + cmd + "' to '" + last[0] + "'")
        return True
