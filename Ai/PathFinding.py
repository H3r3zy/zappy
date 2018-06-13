from Ai import Ai

class PathFinding:
    def __init__(self):
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

    def goToTile(self, player_coords, to):
        nearest_direction = Ai.Direction.NORTH
        range = 0
        if player_coords[0] == to[0] and player_coords[1] != to[1]:  # Je suis en ligne droite Y
            print("Je vais avancer sur les y")
            range, nearest_direction = self.dist(player_coords[1], to[1])

        elif player_coords[1] == to[1] and player_coords[1] != to[0]:  # Je suis en ligne droite X
            range, nearest_direction = self.dist(player_coords[0], to[0])
            nearest_direction = Ai.Direction.WEST if nearest_direction == Ai.Direction.NORTH else Ai.Direction.EAST
        print(nearest_direction)
        print("Range : %d" % range)


'''    def nbOfActions(self, player_coords, x, y):
        action_number = 0
        nearest_direction = Ai.Direction.NORTH
        range = 0
        if player_coords[0] == x and player_coords[1] != y:  # Je suis en ligne droite Y
            print("Je vais avancer sur les y")
            range, nearest_direction = self.dist(player_coords[1], y)
        elif player_coords[1] == y and player_coords[1] != x:  # Je suis en ligne droite X
            range, nearest_direction = self.dist(player_coords[0], x)
            nearest_direction = Ai.Direction.WEST if nearest_direction == Ai.Direction.NORTH else Ai.Direction.EAST
        print(nearest_direction)
        print("Range : %d" % range)
        return action_number
'''