class Tile:
    def __init__(self):
        self.__player = 0
        self.__food = 0
        self.__stones = {"linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0,
                         "food": 0}

    def getPlayer(self) -> int:
        return self.__player

    def getFood(self):
        return self.__food

    def getStones(self):
        return self.__stones

    def reset(self):
        for key, val in self.__stones.items():
            self.__stones[key] = 0

    def setPlayer(self, player: int):

        print("Hey ", player)
        self.__player = player

    def __str__(self):
        return "resources : " + str(self.__stones) + " players :" + str(self.__player)

    def __repr__(self):
        return "resources : " + str(self.__stones) + " players :" + str(self.__player)