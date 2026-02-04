import random
import texttable as tt

class Snake:
    def __init__(self, grid_size, initial_length=3):
        mid = grid_size // 2
        self.body = [(mid, mid + i) for i in range(initial_length)]
        self.direction = (0, -1)
        self.grid_size = grid_size

    def move(self, steps=1):
        """
        Move the snake
        :param steps:
        :return:
        """
        for _ in range(steps):
            head_x, head_y = self.body[0]
            dir_x, dir_y = self.direction
            new_head = (head_x + dir_x, head_y + dir_y)

            # Check for boundary conditions
            if not (0 <= new_head[0] < self.grid_size and 0 <= new_head[1] < self.grid_size):
                raise IndexError("Snake moved out of grid boundaries")

            self.body = [new_head] + self.body[:-1]

    def grow(self):
        self.body.append(self.body[-1])

    def change_direction(self, new_direction):
        """
        Change the direction of the snake
        :param new_direction:
        :return:
        """
        if (self.direction[0] + new_direction[0], self.direction[1] + new_direction[1]) != (0, 0) and new_direction != self.direction:
            self.direction = new_direction

class Grid:
    def __init__(self, size, apples_count):
        self.grid_size = size
        self.grid = [[" " for _ in range(self.grid_size)] for _ in range(self.grid_size)]
        self.apples_count = apples_count
        self.snake = Snake(self.grid_size)
        self.apples = []
        self.place_apples()

    def place_apples(self):
        """
        Place apples on the grid
        :return:
        """
        while len(self.apples) < self.apples_count:
            x, y = random.randint(0, self.grid_size - 1), random.randint(0, self.grid_size - 1)
            if (x, y) not in self.apples and (x, y) not in self.snake.body:
                if all(abs(x - xa) > 1 or abs(y - ya) > 1 for xa, ya in self.apples):
                    self.apples.append((x, y))

    def update_grid(self):
        """
        Update the grid
        :return:
        """
        self.grid = [[" " for _ in range(self.grid_size)] for _ in range(self.grid_size)]
        for x, y in self.snake.body:
            self.grid[x][y] = "+" if (x, y) != self.snake.body[0] else "*"
        for x, y in self.apples:
            self.grid[x][y] = "a"

        table = tt.Texttable()
        for row in self.grid:
            table.add_row(row)

        print(table.draw())



