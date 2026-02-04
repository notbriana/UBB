import random
import texttable as tt

class Grid:
    def __init__(self):
        self.grid_size = 8
        self.grid = [[" " for _ in range(self.grid_size)] for _ in range(self.grid_size)]
        self.stars = []
        self.endeavour_position = None
        self.blingon_positions = []

    def is_adjacent(self, x1, y1, x2, y2):
        """
        Checks if two grid cells are adjacent (row, column, or diagonal)
        :param x1:
        :param y1:
        :param x2:
        :param y2:
        :return:
        """
        return abs(x1 - x2) <= 1 and abs(y1 - y2) <= 1

    def place_stars(self):
        """
        Randomly place stars on the grid
        :return:
        """
        while len(self.stars) < 10:
            x = random.randint(0, 7)
            y = random.randint(0, 7)
            if (x, y) not in self.stars and all(not self.is_adjacent(x, y, sx, sy) for sx, sy in self.stars):
                self.stars.append((x, y))
                self.grid[x][y] = "*"

    def place_endeavour(self):
        """
        Randomly place the Endeavour on the grid
        :return:
        """
        while True:
            x = random.randint(0, 7)
            y = random.randint(0, 7)
            if (x, y) not in self.stars:
                self.endeavour_position = (x, y)
                self.grid[x][y] = "E"
                break

    def place_blingons(self):
        """
        Randomly place the Blingons on the grid
        :return:
        """
        while len(self.blingon_positions) < 3:
            x = random.randint(0, 7)
            y = random.randint(0, 7)

            if (x, y) not in self.stars and (x, y) != self.endeavour_position and  (x, y) not in self.blingon_positions:
                self.blingon_positions.append((x, y))

    def display_grid(self, cheat = False):
        """
        Display the grid
        :param cheat:
        :return:
        """

        table = tt.Texttable()
        header = [" "] + [str(i + 1) for i in range(self.grid_size)]

        table.header(header)

        for i in range(self.grid_size):
            row = [chr(65 + i)]

            for j in range(self.grid_size):
                if (i, j) in self.stars:
                    row.append("*")
                elif (i, j) == self.endeavour_position:
                    row.append("E")
                elif (i, j) in self.blingon_positions and cheat:
                    row.append("B")
                else:
                    row.append(" ")

            table.add_row(row)

        print(table.draw())


class Game:
    def __init__(self):
        self.grid = Grid()
        self.grid.place_stars()
        self.grid.place_endeavour()
        self.grid.place_blingons()
        self.running = True

    def warp(self, target):
        """
        Warp the Endeavour to a new location
        :param target:
        :return:
        """
        target_row = ord(target[0].upper()) - 65
        target_col = int(target[1]) - 1

        if not(0 <= target_col < 8 and 0 <= target_row < 8):
            print("Invalid coordinate")
            return

        current_row, current_col = self.grid.endeavour_position

        if not(
            target_row == current_row
            or target_col == current_col
            or abs(target_row - current_row) == abs(target_col - current_col)
        ):
            print("Invalid warp! You can only warp to a cell in the same row, column, or diagonal")
            return


        if (target_row, target_col) in self.grid.stars:
            print("Star in the way! Invalid warp!")
            return

        if (target_row, target_col) in self.grid.blingon_positions:
            print("You have hit a Blingon! Game over!")
            self.running = False
            return

        self.grid.grid[current_row][current_col] = " "
        self.grid.endeavour_position = (target_row, target_col)
        self.grid.grid[target_row][target_col] = "E"

    def fire(self, target):
        """
        Fire at a Blingon
        :param target:
        :return:
        """
        target_row = ord(target[0].upper()) - 65
        target_col = int(target[1]) - 1

        if not (0 <= target_row < 8 and 0 <= target_col < 8):
            print("Invalid coordinate")
            return

        current_row, current_col = self.grid.endeavour_position

        if not self.grid.is_adjacent(current_row, current_col, target_row, target_col):
            print("Invalid target! You can only fire at an adjacent cell")
            return

        if (target_row, target_col) in self.grid.blingon_positions:
            print("You have hit a Blingon!")
            self.grid.blingon_positions.remove((target_row, target_col))

            if not self.grid.blingon_positions:
                print("Congratulations! You have destroyed all Blingons and won the game!")
                self.running = False
                return

            # Reposition remaining Blingons
            self.grid.grid[target_row][target_col] = " "
            for i in range(len(self.grid.blingon_positions)):
                while True:
                    x = random.randint(0, 7)
                    y = random.randint(0, 7)
                    if (x, y) not in self.grid.stars and (x, y) != self.grid.endeavour_position and (
                    x, y) not in self.grid.blingon_positions:
                        self.grid.blingon_positions[i] = (x, y)
                        break

        else:
            print("Missed!")

    def cheat(self):
        """
        Display the grid with Blingons
        :return:
        """
        self.grid.display_grid(cheat=True)










