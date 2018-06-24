#!/usr/bin/env python
# coding: utf-8

from Ai_Client.Enum.Actions import Actions
from Ai_Client.Client import Client
from Ai_Client.Ai.Ai import Ai
from Ai_Client.Ai.PathFinding import PathFinding


def Synchronise(client: Client, player: Ai):
    if Synchronise.look_id == -1:
        Synchronise.look_id = client.build_command("Look", "", (player.getCoord(), player.getDir()))
        if Synchronise.return_func == Actions.LOOK:
            client.msgQueue.clear()
    if Synchronise.look_id != client.last:
        # if Synchronise.return_func != Actions.LOOK:
        #   client.msgQueue.clear()
        return Actions.SYNCHRO
    Synchronise.look_id = -1
    print(Synchronise.return_func)
    return Synchronise.return_func


Synchronise.return_func = Actions.GO_TO_BROADCASTER
Synchronise.look_id = -1


def Synchronise_inventory(client: Client, player: Ai):
    if Synchronise_inventory.id == -1:
        Synchronise_inventory.id = client.build_command("Inventory")
    if Synchronise_inventory.id != client.last:
        return Actions.SYNCHRO_INVENTORY
    Synchronise_inventory.id = -1
    print(Synchronise_inventory.return_func)
    return Synchronise_inventory.return_func


Synchronise_inventory.return_func = Actions.LOOK
Synchronise_inventory.id = -1


def Synchronise_broadcast(client: Client, player: Ai):
    if Synchronise_broadcast.id == -1:
        Synchronise_broadcast.id = client.build_command("Inventory", Synchronise_broadcast.msg)
    if Synchronise_broadcast.id != client.last:
        return Actions.SYNCHRO_INVENTORY
    Synchronise_broadcast.id = -1
    print(Synchronise_broadcast.return_func)
    return Synchronise_broadcast.return_func


Synchronise_broadcast.msg = "FIRST"
Synchronise_broadcast.return_func = Actions.LOOK
Synchronise_broadcast.id = -1


def look(client: Client, player: Ai):
    if look.id == -1:
        look.id = 1
        Synchronise.return_func = Actions.LOOK
        return Actions.SYNCHRO
    look.id = -1
    return Actions.CHECK_FOOD


look.id = -1


def take_all_resources(client: Client, player: Ai):
    x = player.getCoord()[0] % client.mapSize[0]
    y = player.getCoord()[1] % client.mapSize[1]
    map = player.getMap()
    items = map[y][x].getStones()

    for obj, nb in items.items():
        if nb > 0:
            while nb > 0:
                client.build_command("Take", obj, (x, y))
                nb -= 1


def shifting(client: Client, player: Ai, to_go: list):
    map = player.getMap()
    player_coord = [player.getCoord()[0] % client.mapSize[0], player.getCoord()[1] % client.mapSize[1]]
    finding_path = PathFinding(client.mapSize[1], client.mapSize[0])

    map[player_coord[1]][player_coord[1]].setPlayer(map[player_coord[1]][player_coord[0]].getPlayer() - 1)
    try:
        actions, player.dir = finding_path.goToTile(player.getCoord(), to_go, player.getDir())
        for move in actions:
            client.build_command(move)
    except IndexError:
        print(player.getDir())
    player.setCoord(to_go[0], to_go[1])


def CheckingFood(client: Client, player: Ai):
    client.build_command("Inventory")
    if player.getInventory()["food"] < 5:
        return Actions.FIND_FOOD
    return Actions.CHECK_LVL_UP


def Forward(client: Client, player: Ai):
    x = player.getCoord()[0] % client.mapSize[0]
    y = player.getCoord()[1] % client.mapSize[1]
    x_forward = (x + 1) % client.mapSize[0]
    y_forward = (y + 1) % client.mapSize[1]
    shifting(client, player, [x_forward, y_forward])
    return Actions.LOOK


def CheckLvlUp(_1, player: Ai):
    needed_stones = player.elevation_array[player.getLevel()]
    inventory = player.getInventory()

    for stone, nb in needed_stones:
        if inventory[stone] < nb:
            return Actions.FIND_CRYSTALS
    return Actions.CHECK_PLAYER


def Drop(client: Client, player: Ai):
    client.build_command("Broadcast", "Drop")
    needed_stone = player.elevation_array[player.getLevel()]
    for stone, nb in needed_stone:
        for drop in range(nb):
            client.build_command("Set", stone)
    if player.getBroadcaster():
        print("maiiiis :(")
        take_all_resources(client, player)
        return Actions.LVL_UP
    else:
        print("Comme je suis pas bro bah go lv up")
        return Actions.WAIT_LVL_UP


def IncantBroadCast(client: Client, player: Ai):
    print("Je suis broadcaster")

    if IncantBroadCast.Synchro == -1:
        client.build_command("Look", "", (player.getCoord(), player.getDir()))
        IncantBroadCast.Synchro = 1
        Synchronise_inventory.return_func = Actions.NEED_PEOPLE
        return Actions.SYNCHRO_INVENTORY
    IncantBroadCast.Synchro = -1
    if player.getInventory()["food"] <= 6:
        return Actions.LOOK
    x = player.getCoord()[0]
    y = player.getCoord()[1]
    nb_player = player.elevation_player[player.getLevel()]
    str = "{}: Incantation Lvl {}".format(player.getId(), int(player.getLevel()))
    client.build_command("Broadcast", str)
    if nb_player == player.getMap()[y][x].getPlayer():
        # client.clean()
        print("Je vais drop !!")
        return Actions.DROP
    player.setBroadcaster(True)
    return Actions.NEED_PEOPLE


IncantBroadCast.Synchro = -1


def AmIFirst(client: Client, player: Ai):
    if AmIFirst.synchro == -1:
        AmIFirst.synchro = 1
        Synchronise_broadcast.return_func = Actions.AM_I_FIRST
        Synchronise_broadcast.msg = "FIRST"
        return Actions.SYNCHRO_BROADCAST
    AmIFirst.synchro = -1
    if len(client.msgQueue) < 0:
        print("Someone before me :O")
        return Actions.FIND_IF_BROADCASTER
    else:
        print("MOUAHAHA I'm the first")
        return Actions.NEED_PEOPLE


AmIFirst.synchro = -1


def CheckPlayer(client: Client, player: Ai):
    nb_player = player.elevation_player[player.getLevel()]
    x = player.getCoord()[0] % client.mapSize[0]
    y = player.getCoord()[1] % client.mapSize[1]

    if nb_player != player.getMap()[y][x].getPlayer():
        if nb_player < player.getMap()[y][x].getPlayer():
            return Actions.FORWARD
        if len(client.msgQueue) > 0:
            return Actions.FIND_IF_BROADCASTER
        return Actions.MAKE_FOOD_STOCK
    else:
        return Actions.TAKE_ALL


def TakeAll(client: Client, player: Ai):
    needed_stone = player.elevation_array[player.getLevel()]
    take_all_resources(client, player)
    for stone, nb in needed_stone:
        for drop in range(nb):
            client.build_command("Set", stone)
    return Actions.LVL_UP


def LvlUp(client: Client, player: Ai):
    needed_stones = player.elevation_array[player.getLevel()]

    if LvlUp.Synchro == -1:
        Synchronise.return_func = Actions.LVL_UP
        LvlUp.Synchro = 1
        print("TOOT")
        LvlUp.OldLvl = player.getLevel()
        return Actions.SYNCHRO
    LvlUp.Synchro = -1

    print("Incantation /!\\")
    client.build_command("Incantation")
    client.build_command("Incantation2", "", (), True)
    return Actions.LOOK


LvlUp.OldLvl = 0
LvlUp.Synchro = -1


class ActionNode:
    def __init__(self, func):
        self.func = func

    def action(self, client: Client, player: Ai) -> int:
        return self.func(client, player)
