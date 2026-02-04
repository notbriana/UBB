import texttable as tt

class Grid:
    def __init__(self):
        self.grid_size = 8
        self.grid = [[" " for _ in range(self.grid_size)] for _ in range(self.grid_size)]


    def display_grid(self):
        table = tt.Texttable()
        for row in self.grid:
            table.add_row(row)
        print(table.draw())

    def place_patern(self, patter_name, x, y):
        