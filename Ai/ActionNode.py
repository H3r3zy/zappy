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


def look(client: Client, player: Ai, args):
    if look.id == -1:
        look.id = client.build_command("Look", "", tuple(player.getCoord()))
    if look.id != client.last:
        return Actions.LOOK
    look.id = -1
    return Actions.CHECK_FOOD


look.id = -1


def CheckingFood(client: Client, player: Ai, args):
    client.build_command("Inventory")
    if player.getInventory()["food"] < 5:
        return Actions.FIND_FOOD
    return Actions.FIND_CRYSTALS


def FindFood(client: Client, player: Ai, args):
    print("Je cherche de la food")
    radar = PathFinding.radar(player.getCoord()[0], player.getCoord()[1], 9)
    finding_path = PathFinding(client.mapSize[1], client.mapSize[0])
    map = player.getMap()

    for coord in radar:
        coord[1] %= client.mapSize[1]
        coord[0] %= client.mapSize[0]
        if map[coord[1]][coord[0]].getStones()["food"] != 0:
            actions, player.dir = finding_path.goToTile(player.getCoord(), coord, player.getDir())
            for move in actions:
                client.build_command(move)
            client.build_command("Take", "food", tuple(player.getCoord()))
            return Actions.LOOK
    return Actions.LOOK


def FindCrystals(client: Client, player: Ai, args):
    print("Je cherche des cristaux")
    radar = PathFinding.radar(player.getCoord()[0], player.getCoord()[1], 9)
    finding_path = PathFinding(client.mapSize[1], client.mapSize[0])
    map = player.getMap()
    needed_stones = player.elevation_array[player.getLevel()]

    for coord in radar:
        for stone in needed_stones:
            coord[1] %= client.mapSize[1]
            coord[0] %= client.mapSize[0]
            if map[coord[1]][coord[0]].getStones()[stone] != 0:
                actions, player.dir = finding_path.goToTile(player.getCoord(), coord, player.getDir())
                for move in actions:
                    client.build_command(move)
                client.build_command("Take", stone, tuple(player.getCoord()))
                return Actions.LOOK
    return Actions.LOOK


class ActionNode:
    def __init__(self, node_id: int, func):
        self.id = node_id
        self.func = func

    def action(self, client: Client, player: Ai, args) -> int:
        return self.func(client, player, args)
