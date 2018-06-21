#!/usr/bin/env python
# coding: utf-8

from Ai_Client.Client import Client
from Ai_Client.Ai.Ai import Ai
from enum import IntEnum
from Ai_Client.Ai.PathFinding import PathFinding


class Actions(IntEnum):
    LOOK = 0,
    CHECK_FOOD = 1,  # type: Actions
    FIND_FOOD = 2,
    FIND_CRYSTALS = 3,
    FORWARD = 4,
    CHECK_LVL_UP = 5,
    TAKE_ALL = 6,
    LVL_UP = 7,
    CHECK_PLAYER = 8,
    NEED_PEOPLE = 9


def look(client: Client, player: Ai, _):
    if look.id == -1:
        look.id = client.build_command("Look", "", (player.getCoord(), player.getDir()))
    if look.id != client.last:
        return Actions.LOOK
    look.id = -1
    print("J'ai fini de look")
    return Actions.CHECK_FOOD


look.id = -1


def CheckingFood(client: Client, player: Ai, _):
    client.build_command("Inventory")
    if player.getInventory()["food"] < 5:
        return Actions.FIND_FOOD
    return Actions.CHECK_LVL_UP


def Forward(client: Client, player: Ai, _):
    x = player.getCoord()[0] % client.mapSize[0]
    y = player.getCoord()[1] % client.mapSize[1]
    x_forward = (x + 1) % client.mapSize[0]
    y_forward = (y + 1) % client.mapSize[1]
    map = player.getMap()
    map[y][x].setPlayer(
        map[y][x].getPlayer() - 1)
    finding_path = PathFinding(client.mapSize[1], client.mapSize[0])
    actions, player.dir = finding_path.goToTile([x, y], (x_forward, y_forward), player.dir)
    for move in actions:
        client.build_command(move)
    player.setCoord(x_forward, y_forward)
    map[y_forward][x_forward].setPlayer(map[y_forward][x_forward].getPlayer() + 1)
    return Actions.LOOK


def CheckLvlUp(_1, player: Ai, _2):
    needed_stones = player.elevation_array[player.getLevel()]
    inventory = player.getInventory()

    for stone, nb in needed_stones:
        if inventory[stone] < nb:
            return Actions.FIND_CRYSTALS
    return Actions.CHECK_PLAYER


def IncantBroadCast(client: Client, player: Ai, _):
    print("J'ai besoin de gens à ma case")
    str = "Incantation Lvl %d".format(player.getLevel())
    client.build_command("Broadcast", str)
    return Actions.CHECK_LVL_UP


def CheckPlayer(client: Client, player: Ai, _):
    print("Je check si il y a suffisament de personne")
    nb_player = player.elevation_player[player.getLevel()]
    x = player.getCoord()[0] % client.mapSize[0]
    y = player.getCoord()[1] % client.mapSize[1]

    print("Je suis lvl : %d on doit être : %d on est %d" % (
        player.getLevel(), nb_player, player.getMap()[y][x].getPlayer()))
    if nb_player != player.getMap()[y][x].getPlayer():
        # return Actions.NEED_PEOPLE

        print("Je n'ai pas le bon nombre de joueur")
        '''todo Check Si quelqu'un fait appelle
            sinon broadcast
        '''
        pass
    else:
        return Actions.TAKE_ALL
    return Actions.LOOK
    # todo, broadcast pour savoir le lvl des autres personnes sur la case


def TakeAll(client: Client, player: Ai, _):
    x = player.getCoord()[0] % client.mapSize[0]
    y = player.getCoord()[1] % client.mapSize[1]
    map = player.getMap()
    items = map[y][x].getStones()  # Peut être faire une copie

    for obj, nb in items.items():

        if nb > 0:
            while nb > 0:
                client.build_command("Take", obj, (x, y))
                nb -= 1
    print("La case : %s" % items)
    return Actions.LVL_UP


def LvlUp(client: Client, player: Ai, _):
    needed_stone = player.elevation_array[player.getLevel()]
    needed_player = player.elevation_player[player.getLevel()]

    print("Je drop ce que j'ai besoin : %s je suis lvl : %d" % (player.getInventory(), player.getLevel()))
    for stone, nb in needed_stone:
        for drop in range(nb):
            client.build_command("Set", stone)
    print("Tout est setup")
    client.build_command("Incantation")
    client.build_command("Incantation", "", (), True)
    return Actions.LOOK


def FindCrystals(client: Client, player: Ai, _):
    print("Je cherche des cristaux")
    radar = PathFinding.radar(player.getCoord()[0], player.getCoord()[1], 9)
    finding_path = PathFinding(client.mapSize[1], client.mapSize[0])
    map = player.getMap()
    needed_stones = player.elevation_array[player.getLevel()]

    x = player.getCoord()[0] % client.mapSize[0]
    y = player.getCoord()[1] % client.mapSize[1]
    coord_player = [x, y]
    for stone, _ in needed_stones:
        if map[y][x].getStones()[stone] != 0:
            client.build_command("Take", stone, tuple((x, y)))
    for x, y in radar:
        for stone, _ in needed_stones:
            y %= client.mapSize[1]
            x %= client.mapSize[0]
            if map[y][x].getStones()[stone] != 0:
                map[coord_player[1]][coord_player[0]].setPlayer(map[coord_player[1]][coord_player[0]].getPlayer() - 1)
                actions, player.dir = finding_path.goToTile(player.getCoord(), [x, y], player.getDir())
                for move in actions:
                    client.build_command(move)
                player.setCoord(x, y)
                client.build_command("Take", stone, tuple((x, y)))
                map[y][x].setPlayer(map[y][x].getPlayer() + 1)
                print(player.getInventory())
                return Actions.LOOK
    return Actions.FORWARD


def FindFood(client: Client, player: Ai, _):
    print("Je cherche de la food")
    radar = PathFinding.radar(player.getCoord()[0], player.getCoord()[1], 9)
    finding_path = PathFinding(client.mapSize[1], client.mapSize[0])
    map = player.getMap()

    x = player.getCoord()[0] % client.mapSize[0]
    y = player.getCoord()[1] % client.mapSize[1]
    coord_player = [x, y]
    if map[y][x].getStones()["food"] != 0:
        client.build_command("Take", "food", tuple((x, y)))
    for x, y in radar:
        y %= client.mapSize[1]
        x %= client.mapSize[0]
        if map[y][x].getStones()["food"] != 0:
            map[coord_player[1]][coord_player[0]].setPlayer(map[coord_player[1]][coord_player[0]].getPlayer() - 1)
            actions, player.dir = finding_path.goToTile(player.getCoord(), [x, y], player.getDir())
            for move in actions:
                client.build_command(move)
            player.setCoord(x, y)
            map[y][x].setPlayer(map[y][x].getPlayer() + 1)
            client.build_command("Take", "food", tuple((x, y)))
            return Actions.LOOK
    return Actions.FORWARD


class ActionNode:
    def __init__(self, node_id: int, func):
        self.id = node_id
        self.func = func

    def action(self, client: Client, player: Ai, args) -> int:
        return self.func(client, player, args)
