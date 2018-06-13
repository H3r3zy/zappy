#!/usr/bin/env python
# coding: utf-8

import socket
import select
from Client import CmdParser
from collections import deque


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
        self.__outQueue = deque()
        self.__mapSize = (0, 0)

    def connect(self) -> bool:
        try:
            self.__socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.__socket.connect(("localhost", self.__port))
            print("Connection on port %d successful" % self.__port)
        except socket.error:
            print("Connection on port %d failed" % self.__port)
            return False
        return True

    def updateinbuff(self, con):
        data = con.recv(1024)
        if len(data) == 0:
            raise socket.error('Connection lost')
        self.__inBuff += data.decode("ascii")
        for cmd in self.__inBuff.split("\n"):
            if len(cmd) != 0:
                self.__inQueue.append(cmd)
        self.__inBuff = self.__inBuff.split("\n")[-1]

    def udpateoutbuff(self, con):
        sent = con.send(self.__outBuff.encode("ascii"))
        if sent == 0:
            raise socket.error('Connection lost')
        self.__outBuff = (self.__outBuff.encode("ascii"))[sent:].decode("ascii")

    def buildcommand(self, cmd: str):
        self.__outQueue.append(cmd)
        self.__outBuff += cmd + '\n'

    def refresh(self):
        rcons, wcons, _ = select.select([self.__socket], [self.__socket] if len(self.__outBuff) > 0 else [], [], 0)
        for con in rcons:
            self.updateinbuff(con)
        for con in wcons:
            self.udpateoutbuff(con)

    def getlastresponse(self):
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
                self.buildcommand(self.__name)
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
        parser = CmdParser.CmdParser([], {}, self.__outQueue)
        while True:
            self.refresh()
            self.buildcommand("Look")
            if len(self.__inQueue) > 0:
                parser.parse(self.__inQueue.popleft())
