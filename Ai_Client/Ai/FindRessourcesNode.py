from Ai_Client.Enum.Actions import Actions
from Ai_Client.Client import Client
from Ai_Client.Ai.Ai import Ai
from Ai_Client.Ai.PathFinding import PathFinding
from Ai_Client.Ai.ActionNode import shifting


def FindCrystals(client: Client, player: Ai):
    radar = PathFinding.radar(player.getCoord()[0], player.getCoord()[1], 9)
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
                shifting(client, player, [x, y])
                client.build_command("Take", stone, tuple((x, y)))
                map[y][x].setPlayer(map[y][x].getPlayer() + 1)
                return Actions.LOOK
    return Actions.FORWARD


def FindFood(client: Client, player: Ai):
    radar = PathFinding.radar(player.getCoord()[0], player.getCoord()[1], 9)
    map = player.getMap()

    x = player.getCoord()[0] % client.mapSize[0]
    y = player.getCoord()[1] % client.mapSize[1]
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
