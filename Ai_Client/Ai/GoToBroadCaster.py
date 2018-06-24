from Ai_Client.Ai.ActionNode import *
import re


def WaitLvlUp(client: Client, player: Ai):
    if WaitLvlUp.lvl == -1:
        WaitLvlUp.lvl = player.getLevel()
    elif WaitLvlUp.lvl != player.getLevel():
        WaitLvlUp.lvl = -1
        return Actions.LOOK
    if len(client.msgQueue) != 0:
        while len(client.msgQueue) > 0:
            msg = client.msgQueue.popleft()
            if msg[0] != "0":
                continue
            if msg[1] == "Fail Incant":
                return Actions.LOOK
    return Actions.WAIT_LVL_UP


WaitLvlUp.lvl = -1


def GoToBroadCaster(client: Client, player: Ai):
    player_coord = player.getCoord()
    map = player.getMap()

    if GoToBroadCaster.lookId == -1:
        GoToBroadCaster.lookId = 1
        Synchronise.return_func = Actions.GO_TO_BROADCASTER
        return Actions.SYNCHRO
    GoToBroadCaster.lookId = -1
    if map[player_coord[1]][player_coord[0]].getStones()["food"] != 0:
        for nb in range(map[player_coord[1]][player_coord[0]].getStones()["food"]):
            if nb > 3:
                break
            client.build_command("Take", "food", player_coord)
    while len(client.msgQueue) > 0:
        msg = client.msgQueue.popleft()
        lvl = re.match("(\d+): Incantation Lvl (\d)", msg[1])
        if lvl and int(lvl.group(2)) == player.getLevel():
            GoToBroadCaster.lookId = -1
            if msg[0] == 0:
                return Actions.WAIT_LVL_UP
            new_coord = player.WhereIs(msg[0])
            shifting(client, player, new_coord)
            return Actions.GO_TO_BROADCASTER
    return Actions.GO_TO_BROADCASTER


GoToBroadCaster.TimeToStop = 0
GoToBroadCaster.FollowId = 0
GoToBroadCaster.lookId = 0


def FindIfBroadCaster(client: Client, player: Ai):
    while len(client.msgQueue) > 0:
        msg = client.msgQueue.popleft()
        lvl = re.match("(\d+): Incantation Lvl (\d)", msg[1])
        if lvl and int(lvl.group(2)) == player.getLevel():
            new_coord = player.WhereIs(msg[0])
            shifting(client, player, new_coord)
            GoToBroadCaster.FollowId = int(lvl.group(1))
            return Actions.GO_TO_BROADCASTER
    return Actions.NEED_PEOPLE
