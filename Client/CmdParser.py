#!/usr/bin/env python
# coding: utf-8

import re
from Client import Client


class CmdParser:
    def __init__(self, map, inv: dict, queue):
        self.__map = map
        self.__inv = inv
        self.__queue = queue
        self.__patterns = {
            'Look': re.compile("\[(( \w+)*(,( \w+)*)* )?\]", re.ASCII),
            'Inventory': re.compile("\[(( \w+ \d+)(, \w+ \d+)* )?\]", re.ASCII),
            'Connect_nbr': re.compile("%d+", re.ASCII),
            'Incantation': re.compile("(Elevation underway Current level: \d)|(ko)", re.ASCII),
            'Forward': re.compile("ok", re.ASCII),
            'Right': re.compile("ok", re.ASCII),
            'Left': re.compile("ok", re.ASCII),
            'Broadcast Text': re.compile("ok", re.ASCII),
            'Fork': re.compile("ok", re.ASCII),
            'Eject': re.compile("(ok)|(ko)", re.ASCII),
            'Take Object': re.compile("(ok)|(ko)", re.ASCII),
            'Set Object': re.compile("(ok)|(ko)", re.ASCII)
        }

    def parse(self, cmd: str) -> bool:
        if str == "dead":
            return False
        if self.__queue[0] in self.__patterns:
            match = self.__patterns[self.__queue.popleft()].match(cmd)
            print(match.group(0))
        else:
            raise Client.ZappyException('Unexpected response ' + cmd)
