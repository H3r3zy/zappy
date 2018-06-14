from Ai import Ai


class PathFinding:
    def __init__(self, mapsize_x, mapsize_y):
        self.__mapsize_x = mapsize_x
        self.__mapsize_y = mapsize_y
        pass

    def dist(self, player_coord, coord):
        range = 0
        nearest_dir = Ai.Direction.NORTH
        print("coord_player : %d && coord : %d" % (player_coord, coord))
        if player_coord > coord:
            range = player_coord - coord
        elif coord > player_coord:
            nearest_dir = Ai.Direction.SOUTH
            range = coord - player_coord
        return range, nearest_dir

    def move(self, normal_range, opposite_range, player_dir):
        actions = []
        if normal_range[1] != player_dir and normal_range[0] + 2 < opposite_range[0]:
            actions.append("Right")
            actions.append("Right")
            player_dir = normal_range[1]
            for i in range(0, normal_range[0]):
                actions.append("Forward")
        elif normal_range[0] <= opposite_range[0]:
            print("normal range : %d" % normal_range[0])
            '''if normal_range[1] != player_dir:  # Ne peux pas arriver
                actions.append("Right")
                actions.append("Right")
                player_dir = normal_range[1]'''
            for i in range(normal_range[0]):
                actions.append("Forward")
        else:
            print("opposite range : %d" % opposite_range[0])
            if opposite_range[1] != player_dir:
                actions.append("Right")
                actions.append("Right")
                player_dir = opposite_range[1]
            for i in range(opposite_range[0]):
                actions.append("Forward")
        return actions, player_dir

    def moveUpOrDown(self, player_coords, to, player_dir):
        normal_range = [0, Ai.Direction.NORTH]
        print("Je vais avancer sur les y")
        normal_range[0], normal_range[1] = self.dist(player_coords[1], to[1])
        print("distance : %d, dir : %s" % (normal_range[0], normal_range[1]))
        opposite_range = [
            self.__mapsize_y - normal_range[0],
            Ai.Direction.NORTH if normal_range[1] == Ai.Direction.SOUTH else Ai.Direction.SOUTH]
        actions, player_dir = self.move(normal_range, opposite_range, player_dir)
        return actions, player_dir

    def moveLeftOrRight(self, player_coords, to, player_dir):
        normal_range = [0, Ai.Direction.NORTH]
        normal_range[0], normal_range[1] = self.dist(player_coords[0], to[0])
        normal_range[1] = Ai.Direction.WEST if normal_range[1] == Ai.Direction.NORTH else Ai.Direction.EAST
        opposite_range = [
            self.__mapsize_x - normal_range[0],
            Ai.Direction.EAST if normal_range[1] == Ai.Direction.WEST else Ai.Direction.WEST]
        actions, player_dir = self.move(normal_range, opposite_range, player_dir)
        return actions, player_dir

    def goToTile(self, player_coords, to, player_dir):
        nb_actions = 0
        actions = []

        if player_coords[0] != to[0] and player_coords[1] != to[1]:  # Diagonales
            if player_dir == Ai.Direction.NORTH or player_dir == Ai.Direction.SOUTH:
                actions, player_dir = self.moveUpOrDown(player_coords, (player_coords[0], to[1]), player_dir)
                player_dir = Ai.Direction.EAST #TODO Bifurcation
                actions.append("Right")
                player_coords[1] = to[1]
                tmp, player_dir = self.moveLeftOrRight(player_coords, to, player_dir)
                actions += tmp
                print(actions)
            else:
                actions, player_dir = self.moveUpOrDown(player_coords, (to[0], player_coords[1]), player_dir)
                actions.append("Right")
                player_dir = Ai.Direction.SOUTH
                player_coords[0] = to[0]
                tmp, player_dir = self.moveLeftOrRight(player_coords, to, player_dir)
                actions += tmp
                print(actions)
        else:
            if player_coords[0] == to[0]:  # Je suis en ligne droite Y
                actions, player_dir = self.moveUpOrDown(player_coords, to, player_dir)
                print(actions)
            elif player_coords[1] == to[1]:  # Je suis en ligne droite X
                actions, player_dir = self.moveLeftOrRight(player_coords, to, player_dir)
                print(actions)
