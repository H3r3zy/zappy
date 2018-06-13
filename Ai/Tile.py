class Tile:
    def __init__(self):
        self.__player = 0
        self.__food = 0
        self.__stones = {"linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}

    def getPlayer(self):
        return self.__player

    def getFood(self):
        return self.__food

    def getStones(self):
        return self.__stones