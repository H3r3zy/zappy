#!/usr/bin/env python
# coding: utf-8

from Ai_Client.Client import Client
from Ai_Client.Ai.Ai import Ai
from enum import IntEnum
from Ai_Client.Ai.PathFinding import PathFinding
import re


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
    NEED_PEOPLE = 9,
    DROP = 10,
    WAIT_ALL_DROPS = 11,
    WAIT_LVL_UP = 12,
    GO_TO_BROADCASTER = 13,
    FIND_IF_BROADCASTER = 14,
    WAIT_TO_DROP = 15,


def look(client: Client, player: Ai):
    if look.id == -1:
        client.msgQueue.clear()
        look.id = client.build_command("Look", "", (player.getCoord(), player.getDir()))
    if look.id != client.last:
        return Actions.LOOK
    look.id = -1
    print("J'ai fini de look")
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
    actions, player.dir = finding_path.goToTile(
        player.getCoord(),
        to_go,
        player.getDir())
    for move in actions:
        client.build_command(move)
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
        return Actions.WAIT_ALL_DROPS
    else:
        return Actions.WAIT_LVL_UP


def WaitDrop(client: Client, player: Ai):
    need_player = player.elevation_player[player.getLevel()]
    while len(client.msgQueue) > 0:
        msg = client.msgQueue.popleft()
        if msg[0] == 0 and msg[1] == "Drop":
            WaitDrop.nb_resp += 1
    if WaitDrop.nb_resp < need_player:
        return Actions.DROP
    return Actions.LVL_UP


WaitDrop.nb_resp = 1


def IncantBroadCast(client: Client, player: Ai):
    # todo Vérifier que je vais pas crever ^^
    print("Je suis broadcaster")
    take_all_resources(client, player)
    x = player.getCoord()[0]
    y = player.getCoord()[1]
    nb_player = player.elevation_player[player.getLevel()]
    if nb_player == player.getMap()[y][x].getPlayer():
        return Actions.DROP
    player.setBroadcaster(True)
    str = "Incantation Lvl {}".format(int(player.getLevel()))
    client.build_command("Broadcast", str)
    return Actions.NEED_PEOPLE


def WaitLvlUp(client: Client, player: Ai):
    if WaitLvlUp.lvl == -1:
        print("C'est ma première iter ! ;)")
        WaitLvlUp.lvl = player.getLevel()
    elif WaitLvlUp.lvl != player.getLevel():
        print("J'ai lvl UP <3")
        WaitLvlUp.lvl = -1
        return Actions.LOOK
    return Actions.WAIT_LVL_UP


WaitLvlUp.lvl = -1


def WaitToDrop(client: Client, player: Ai):
    while len(client.msgQueue) > 0:
        msg = client.msgQueue.popleft()
        if msg[0] == 0 and msg[1] == "Drop":
            return Actions.DROP
    return Actions.WAIT_TO_DROP


def GoToBroadCaster(client: Client, player: Ai):
    #Synchro les players
    player_coord = player.getCoord()
    map = player.getMap()

    if map[player_coord[1]][player_coord[0]].getStones()["food"] != 0:
        client.build_command("Take", "food", player_coord)

    while len(client.msgQueue) > 0:
        msg = client.msgQueue.popleft()
        print("Quelqu'un Broadcasting  :::: " + str(msg))
        lvl = re.match("Incantation Lvl (\d)", msg[1])
        print(lvl.group(1))
        if int(lvl.group(1)) == player.getLevel():
            if msg[0] == 0:
                return Actions.WAIT_TO_DROP
            new_coord = player.WhereIs(msg[0])
            shifting(client, player, new_coord)
            print("Je me déplace vers lui")
            client.msgQueue.clear()
            # Todo Déplacer 1 fois et attendre la response encore, jusqu'a ce que je la recoive sur message 0
            return Actions.GO_TO_BROADCASTER
    return Actions.GO_TO_BROADCASTER


def FindIfBroadCaster(client: Client, player: Ai):
    while len(client.msgQueue) > 0:
        msg = client.msgQueue.popleft()
        print("Quelqu'un Broadcast : " + str(msg))
        lvl = re.match("Incantation Lvl (\d)", msg[1])
        print("Le monsieur est lvl : %d et moi %d " % (int(lvl.group(1)), player.getLevel()))
        if int(lvl.group(1)) == player.getLevel():
            print("j'y vais :D")
            new_coord = player.WhereIs(msg[0])
            shifting(client, player, new_coord)

            # Todo Déplacer 1 fois et attendre la response encore, jusqu'a ce que je la recoive sur message 0
            return Actions.GO_TO_BROADCASTER
    print("Aucun des messages est interressant alors je vais broad moi même")
    return Actions.NEED_PEOPLE


def CheckPlayer(client: Client, player: Ai):
    nb_player = player.elevation_player[player.getLevel()]
    x = player.getCoord()[0] % client.mapSize[0]
    y = player.getCoord()[1] % client.mapSize[1]

    # todo Gestion d'ID
    if nb_player != player.getMap()[y][x].getPlayer():
        if nb_player < player.getMap()[y][x].getPlayer():
            pass
            #return Actions.FORWARD
        if len(client.msgQueue) > 0:
            pass
            #return Actions.FIND_IF_BROADCASTER
        # Je dois y aller !
        #return Actions.NEED_PEOPLE
        return Actions.FORWARD
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
    needed_player = player.elevation_player[player.getLevel()]

    client.build_command("Incantation")
    client.build_command("Incantation", "", (), True)
    return Actions.LOOK


def FindCrystals(client: Client, player: Ai):
    # print("Je cherche des cristaux")
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
                shifting(client, player, [x, y])
                client.build_command("Take", stone, tuple((x, y)))
                map[y][x].setPlayer(map[y][x].getPlayer() + 1)
                return Actions.LOOK
    return Actions.FORWARD


def FindFood(client: Client, player: Ai):
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
            shifting(client, player, [x, y])
            map[y][x].setPlayer(map[y][x].getPlayer() + 1)
            client.build_command("Take", "food", tuple((x, y)))
            return Actions.LOOK
    return Actions.FORWARD


class ActionNode:
    def __init__(self, node_id: int, func):
        self.id = node_id
        self.func = func

    def action(self, client: Client, player: Ai) -> int:
        return self.func(client, player)
