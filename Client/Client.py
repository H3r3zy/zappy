#!/usr/bin/env python3
# coding: utf-8

import socket
import select
from Client import CmdParser
from collections import deque
from Ai.ActionNode import *
from Ai.Ai import *


class ZappyException(Exception):
    pass


class Client:
    def __init__(self, port: int, name: str, machine: str):
        self.__port = port
        self.__name = name
        self.__machine = machine
        self.__socket = None
        self.__inBuff = ""
        self.__outBuff = ""
        self.__inQueue = deque()
        self.__topQueue = deque()
        self.__outQueue = deque(maxlen=10)
        self.mapSize = (0, 0)
        self.wait = 0
        self.__currentNode = Actions.LOOK
        self.__msgQueue = deque()
        self.__nodes = [
            ActionNode(Actions.LOOK, look),
            ActionNode(Actions.CHECK_FOOD, CheckingFood),
            ActionNode(Actions.FIND_FOOD, FindFood),
            ActionNode(Actions.FIND_CRYSTALS, FindCrystals),
        ]
        self.__args = {
            Actions.LOOK: [],
            Actions.CHECK_FOOD: [1, 2],
            Actions.FIND_FOOD: [1, 2],
            Actions.FIND_CRYSTALS: [1, 2],
        }
        self.__outId = 0
        self.last = 0

    def connect(self) -> bool:
        try:
            self.__socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.__socket.connect(("localhost", self.__port))
            print("Connection on port %d successful" % self.__port)
        except socket.error:
            print("Connection on port %d failed" % self.__port)
            return False
        return True

    def update_inbuff(self, con):
        data = con.recv(1024)
        if len(data) == 0:
            raise socket.error('Connection lost')
        self.__inBuff += data.decode("ascii")
        for cmd in self.__inBuff.split("\n"):
            if len(cmd) != 0:
                self.__inQueue.append(cmd)
        self.__inBuff = self.__inBuff.split("\n")[-1]

    def udpate_outbuff(self, con, mode: bool = False):
        if mode:
            self.refresh_queue()
        sent = con.send(self.__outBuff.encode("ascii"))
        if sent == 0:
            raise socket.error('Connection lost')
        self.__outBuff = (self.__outBuff.encode("ascii"))[sent:].decode("ascii")

    def refresh_queue(self):
        while len(self.__outQueue) != self.__outQueue.maxlen and len(self.__topQueue) > 0:
            tup = self.__topQueue.popleft()
            self.__outBuff += tup[0] + (" " if len(tup[1]) > 0 else "") + '\n'
            self.__outQueue.append(tup[0])

    def build_command(self, cmd: str, arg: str = "") -> int:
        self.__topQueue.append((cmd, arg, self.__outId))
        self.__outId += 1
        self.refresh_queue()
        return self.__outId - 1

    def refresh(self, mode: bool = False):
        rcons, wcons, _ = select.select([self.__socket], [self.__socket] if len(self.__outBuff) > 0 else [], [], 0)
        for con in rcons:
            self.update_inbuff(con)
        for con in wcons:
            self.udpate_outbuff(con, mode)

    def get_last_response(self):
        if len(self.__inQueue) > 0:
            return self.__inQueue.popleft()
        return None

    def auth(self):
        welcome = False
        while True:
            self.refresh()
            if len(self.__inQueue) >= 1 and welcome is False:
                resp = self.__inQueue.popleft()
                if resp != "WELCOME":
                    raise ZappyException('Unexpected response')
                self.build_command(self.__name)
                welcome = True
            if len(self.__inQueue) == 2 and welcome is True:
                try:
                    int(self.__inQueue.popleft())
                    self.mapSize = tuple(map(int, self.__inQueue.popleft().split(" ")))
                except ValueError:
                    raise ZappyException('Unexpected response')
                break
        self.__outQueue.clear()
        self.__outId = 0

    def run(self):
        self.auth()
        ordinal = lambda n: "%d%s" % (n, "tsnrhtdd"[(n / 10 % 10 != 1) * (n % 10 < 4) * n % 10::4])
        print("Authentication successful, map size of %d x %d" % (self.mapSize[0], self.mapSize[1]))
        player = Ai(self.mapSize[1], self.mapSize[0])
        parser = CmdParser.CmdParser(player, self.__outQueue, self.__msgQueue,
                                     (self.__port, self.__name, self.__machine))
        while True:
            self.refresh()
            self.refresh_queue()
            if len(self.__inQueue) > 0:
                if not parser.parse(self.__inQueue.popleft()):
                    print("I died being at the %s level" % ordinal(player.getLevel()))
                    return
            self.last = parser.get_last()
            self.__currentNode = self.__nodes[self.__currentNode].action(self, player,
                                                                         self.__args[self.__currentNode])