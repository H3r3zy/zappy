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
        self.__mapSize = (0, 0)
        self.wait = 0
        self.__currentNode = 0
        self.__nodes = [
            ActionNode(0, look),
            ActionNode(1, node_action0),
            ActionNode(2, node_action0),
            ActionNode(3, node_action0),
            ActionNode(4, node_action0),
            ActionNode(5, node_action0),
            ActionNode(6, node_action0),
            ActionNode(7, node_action0),
            ActionNode(8, node_action0),
            ActionNode(9, node_action0),
        ]
        self.__args = {
            0: [],
            1: [1, 2]
        }

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

    def build_command(self, cmd: str, arg: str = ""):
        self.__topQueue.append((cmd, arg))
        self.refresh_queue()

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
            if len(self.__inQueue) >= 2 and welcome is True:
                try:
                    int(self.__inQueue.popleft())
                    self.__mapSize = tuple(map(int, self.__inQueue.popleft().split(" ")))
                except ValueError:
                    raise ZappyException('Unexpected response')
                break
        self.__outQueue.clear()

    def run(self):
        self.auth()
        print("Authentication successful, map size of %d x %d" % (self.__mapSize[0], self.__mapSize[1]))
        player = Ai(self.__mapSize[0], self.__mapSize[1])
        parser = CmdParser.CmdParser(player, self.__outQueue)
        while True:
            self.refresh()
            self.refresh_queue()
            if len(self.__inQueue) > 0:
                if not parser.parse(self.__inQueue.popleft()):
                    print("I died")
                    return
            self.__currentNode = self.__nodes[self.__currentNode].action(self,
                                                                                      self.__args[self.__currentNode])
