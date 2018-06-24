#!/usr/bin/env python3
# coding: utf-8

import socket
import select
from Ai_Client.Client import CmdParser
from collections import deque
from Ai_Client.Ai.FindRessourcesNode import *
from Ai_Client.Ai.GoToBroadCaster import *
from Ai_Client.Ai.MakeFoodStock import *


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
        self.__nodes = {
            Actions.LOOK: ActionNode(look),
            Actions.CHECK_FOOD: ActionNode(CheckingFood),
            Actions.FIND_FOOD: ActionNode(FindFood),
            Actions.FIND_CRYSTALS: ActionNode(FindCrystals),
            Actions.FORWARD: ActionNode(Forward),
            Actions.CHECK_LVL_UP: ActionNode(CheckLvlUp),
            Actions.TAKE_ALL: ActionNode(TakeAll),
            Actions.LVL_UP: ActionNode(LvlUp),
            Actions.CHECK_PLAYER: ActionNode(CheckPlayer),
            Actions.NEED_PEOPLE: ActionNode(IncantBroadCast),
            Actions.DROP: ActionNode(Drop),
            Actions.WAIT_LVL_UP: ActionNode(WaitLvlUp),
            Actions.GO_TO_BROADCASTER: ActionNode(GoToBroadCaster),
            Actions.FIND_IF_BROADCASTER: ActionNode(FindIfBroadCaster),
            Actions.SYNCHRO: ActionNode(Synchronise),
            Actions.MAKE_FOOD_STOCK: ActionNode(MakeFoodStock),
            Actions.FIND_FOOD_STOCK: ActionNode(FindFoodStock),
            Actions.FORWARD_STOCK: ActionNode(ForwardStock),
            Actions.SYNCHRO_INVENTORY: ActionNode(Synchronise_inventory),
            Actions.SYNCHRO_BROADCAST: ActionNode(Synchronise_broadcast),
            Actions.AM_I_FIRST: ActionNode(AmIFirst)
        }
        self.msgQueue = deque()
        self.__outId = 0
        self.last = 0

    def connect(self) -> bool:
        try:
            self.__socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.__socket.connect((self.__machine, self.__port))
            print("Connection on %s:%d successful" % (self.__machine, self.__port))
        except socket.error:
            print("Connection on %s:%d failed" % (self.__machine, self.__port))
            return False
        return True

    def clean(self):
        self.__outId -= len(self.__topQueue)
        self.__topQueue.clear()

    def update_inbuff(self, con):
        data = con.recv(4096)
        if len(data) == 0:
            raise socket.error('Connection lost')
        self.__inBuff += data.decode("ascii")
        while self.__inBuff.find("\n") != -1:
            cmd = self.__inBuff.partition("\n")
            if len(cmd[0]) != 0 and cmd[1] == "\n":
                self.__inQueue.append(cmd[0])
            self.__inBuff = cmd[2]

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
            if tup[3]:
                self.__outQueue.append(tup[:3])
                continue
            self.__outBuff += tup[0] + (" " + tup[1] if len(tup[1]) > 0 else "") + '\n'
            self.__outQueue.append(tup)

    def build_command(self, cmd: str, arg: str = "", pos: tuple = (0, 0), fake: bool = False) -> int:
        self.__topQueue.append((cmd, arg, pos, fake))
        self.__outId += 1
        self.refresh_queue()
        return self.__outId

    def refresh(self, mode: bool = False):
        rcons, wcons, _ = select.select([self.__socket], [self.__socket] if len(self.__outBuff) > 0 else [], [], 0.01)
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
            if "ko" in self.__inQueue:
                print(self.__inQueue.pop())
                raise ZappyException('Unexpected response')
        self.__outQueue.clear()
        self.__outId = 0

    def run(self):
        self.auth()
        ordinal = lambda n: "%d%s" % (n, "tsnrhtdd"[(n / 10 % 10 != 1) * (n % 10 < 4) * n % 10::4])
        print("Authentication successful, map size of %d x %d" % (self.mapSize[0], self.mapSize[1]))
        player = Ai(self.mapSize[1], self.mapSize[0])
        parser = CmdParser.CmdParser(player, self.__outQueue, self.msgQueue,
                                     (self.__port, self.__name, self.__machine))
        while True:
            self.refresh()
            self.refresh_queue()
            if "dead" in self.__inQueue:
                print("I died being at the %s level" % ordinal(player.getLevel()))
                exit(0)
            if player.getLevel() == 8:
                print("I won !")
                exit(0)
            while len(self.__inQueue) > 0:
                parser.parse(self.__inQueue.popleft())
            self.last = parser.get_last()
            self.__currentNode = self.__nodes[self.__currentNode].action(self, player)
