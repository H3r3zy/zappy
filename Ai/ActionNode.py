#!/usr/bin/env python
# coding: utf-8

from Client import Client
from Ai.Ai import Ai
from enum import IntEnum


class Actions(IntEnum):
    LOOK = 0,
    CHECK_FOOD = 1,  # type: Actions
    FIND_FOOD = 2,
    FIND_CRYSTALS = 3,


def look(client: Client, player: Ai, args):
    client.build_command("Look")
    return Actions.CHECK_FOOD


def CheckingFood(client: Client, player: Ai, args):
    client.build_command("Inventory")
    print("Il me reste : %d bouffe" % player.getInventory()["food"])
    if player.getInventory()["food"] < 5:
        return Actions.FIND_FOOD
    return Actions.FIND_CRYSTALS


def FindFood(client: Client, player: Ai, args):
    print("Je dois vite chercher de la food !!")
    return Actions.LOOK


def FindCrystals(client: Client, player: Ai, args):
    print("Je suis large en nouriture alors go chercher de quoi pex ;)")
    return Actions.LOOK


class ActionNode:
    def __init__(self, node_id: int, func):
        self.id = node_id
        self.func = func

    def action(self, client: Client, player: Ai, args) -> int:
        return self.func(client, player, args)
