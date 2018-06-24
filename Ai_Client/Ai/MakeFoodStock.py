from Ai_Client.Ai.ActionNode import *
from Ai_Client.Ai.GoToBroadCaster import *
import re


def ForwardStock(client: Client, player: Ai):
    x = player.getCoord()[0] % client.mapSize[0]
    y = player.getCoord()[1] % client.mapSize[1]
    x_forward = (x - 1) % client.mapSize[0]
    y_forward = (y - 1) % client.mapSize[1]
    shifting(client, player, [x_forward, y_forward])
    return Actions.MAKE_FOOD_STOCK


def FindFoodStock(client: Client, player: Ai):
    radar = PathFinding.radar(player.getCoord()[0], player.getCoord()[1], 9)
    map = player.getMap()

    x = player.getCoord()[0] % client.mapSize[0]
    y = player.getCoord()[1] % client.mapSize[1]
    if len(client.msgQueue) > 0:
        if FindIfBroadCaster(client, player) == Actions.GO_TO_BROADCASTER:
            return Actions.GO_TO_BROADCASTER
    if map[y][x].getStones()["food"] != 0:
        if map[y][x].getStones()["food"] > 5:
            if FindFoodStock.Synchro == -1:
                FindFoodStock.Synchro = 1
                Synchronise.return_func = Actions.MAKE_FOOD_STOCK
                return Actions.SYNCHRO
            FindFoodStock.Synchro = -1
        for nb in range(map[y][x].getStones()["food"]):
            client.build_command("Take", "food", tuple((x, y)))
    for x, y in radar:
        y %= client.mapSize[1]
        x %= client.mapSize[0]
        if map[y][x].getStones()["food"] != 0:
            shifting(client, player, [x, y])
            map[y][x].setPlayer(map[y][x].getPlayer() + 1)
            if FindFoodStock.Synchro == -1:
                FindFoodStock.Synchro = 1
                Synchronise.return_func = Actions.MAKE_FOOD_STOCK
                return Actions.SYNCHRO
            FindFoodStock.Synchro = -1
            for nb in range(map[y][x].getStones()["food"]):
                client.build_command("Take", "food", tuple((x, y)))
            return Actions.MAKE_FOOD_STOCK
    return Actions.FORWARD_STOCK


FindFoodStock.Synchro = -1


def MakeFoodStock(client: Client, player: Ai):
    if MakeFoodStock.Synchro == -1:
        Synchronise.return_func = Actions.MAKE_FOOD_STOCK
        MakeFoodStock.Synchro = 1
        return Actions.SYNCHRO
    MakeFoodStock.Synchro = -1
    if player.getInventory()["food"] < 25:
        return Actions.FIND_FOOD_STOCK
    return Actions.AM_I_FIRST


MakeFoodStock.Synchro = -1
