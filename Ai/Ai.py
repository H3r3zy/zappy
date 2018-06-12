class Ai:

    def __init__(self):
        print("Je suis crée")

    def Think(self):
        inventory = {"food": 10, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}

        for key in inventory:
            print("Key : %s --> value %d" % (key, inventory[key]))

        self.update(inventory)
        print(inventory)