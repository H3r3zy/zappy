#!/usr/bin/env python
# coding: utf-8

from Client import Client
from Ai.Ai import Ai
from enum import IntEnum
from Ai.PathFinding import PathFinding


class Actions(IntEnum):
    LOOK = 0,
    CHECK_FOOD = 1,  # type: Actions
    FIND_FOOD = 2,
    FIND_CRYSTALS = 3,
    FORWARD = 4,
    CHECK_LVL_UP = 5,


def look(client: Client, player: Ai, _):
    if look.id == -1:
        look.id = client.build_command("Look", "", tuple(player.getCoord()))
    if look.id != client.last:
        return Actions.LOOK
    look.id = -1
    return Actions.CHECK_FOOD


look.id = -1


def CheckingFood(client: Client, player: Ai, _):
    client.build_command("Inventory")
    if player.getInventory()["food"] < 5:
        return Actions.FIND_FOOD
    return Actions.CHECK_LVL_UP


def Forward(client: Client, player: Ai, _):
    print("Pas de truc au alentour, je me déplace aléatoirement")
    finding_path = PathFinding(client.mapSize[1], client.mapSize[0])
    coords = player.getCoord()
    actions, player.dir = finding_path.goToTile(coords, (coords[0] + 1, coords[1] + 1), player.dir)
    for move in actions:
        client.build_command(move)
    print("Du coup je suis en %s" % player.getCoord())
    return Actions.LOOK


def FindFood(client: Client, player: Ai, _):
    print("Je cherche de la food")
    radar = PathFinding.radar(player.getCoord()[0], player.getCoord()[1], 9)
    finding_path = PathFinding(client.mapSize[1], client.mapSize[0])
    map = player.getMap()

    x = player.getCoord()[0] % client.mapSize[0]
    y = player.getCoord()[1] % client.mapSize[1]
    if map[y][x].getStones()["food"] != 0:
        client.build_command("Take", "food", tuple((x, y)))
    for x, y in radar:
        y %= client.mapSize[1]
        x %= client.mapSize[0]
        if map[y][x].getStones()["food"] != 0:
            actions, player.dir = finding_path.goToTile(player.getCoord(), [x, y], player.getDir())
            for move in actions:
                client.build_command(move)
            client.build_command("Take", "food", tuple((x, y)))
            return Actions.LOOK
    return Actions.FORWARD


def CheckLvlUp(_, player: Ai, _):
    print("Je check si je peux up")
    needed_stones = player.elevation_array[player.getLevel()]
    inventory = player.getInventory()

    for stone, nb in needed_stones:
        if inventory[stone] < nb:
            return Actions.FIND_CRYSTALS
    return Actions.TAKE_ALL

def TakeAll(client: Client, player: Ai, _):
    x = player.getCoord()[0] % client.mapSize[0]
    y = player.getCoord()[1] % client.mapSize[1]
    map = player.getMap()
    for obj, nb in map[y][x].getStones():
        if nb > 0:
            while nb > 0:
                client.build_command("Take", obj, (x, y))
                nb -= 1
            

def FindCrystals(client: Client, player: Ai, _):
    print("Je cherche des cristaux")
    radar = PathFinding.radar(player.getCoord()[0], player.getCoord()[1], 9)
    finding_path = PathFinding(client.mapSize[1], client.mapSize[0])
    map = player.getMap()
    needed_stones = player.elevation_array[player.getLevel()]

    x = player.getCoord()[0] % client.mapSize[0]
    y = player.getCoord()[1] % client.mapSize[1]
    for stone, _ in needed_stones:
        if map[y][x].getStones()[stone] != 0:
            client.build_command("Take", stone, tuple((x, y)))
    for x, y in radar:
        for stone, _ in needed_stones:
            y %= client.mapSize[1]
            x %= client.mapSize[0]
            if map[y][x].getStones()[stone] != 0:
                actions, player.dir = finding_path.goToTile(player.getCoord(), [x, y], player.getDir())
                for move in actions:
                    client.build_command(move)
                client.build_command("Take", stone, tuple((x, y)))
                print(player.getInventory())
                return Actions.LOOK
    return Actions.FORWARD


class ActionNode:
    def __init__(self, node_id: int, func):
        self.id = node_id
        self.func = func

    def action(self, client: Client, player: Ai, args) -> int:
        return self.func(client, player, args)
