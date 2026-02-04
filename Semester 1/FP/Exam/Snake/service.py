from domain import Grid


class SnakeGame:
    def __init__(self, grid_size, apples_count):
        self.grid = Grid(grid_size, apples_count)
        self.game_over = False

    def update(self, steps = 1):
        """
        Update the game
        :param steps:
        :return:
        """
        self.grid.snake.move(steps)
        head = self.grid.snake.body[0]
        if head in self.grid.apples:
            self.grid.snake.grow()
            self.grid.apples.remove(head)
            self.grid.place_apples()
        self.check_collision()
        self.grid.update_grid()


    def check_collision(self):
        head = self.grid.snake.body[0]
        if head[0] < 0 or head[0] >= self.grid.grid_size or head[1] < 0 or head[1] >= self.grid.grid_size:
            self.game_over = True

        if head in self.grid.snake.body[1:]:
            self.game_over = True

    def change_snake_direction(self, new_direction):
        """
        Change the direction of the snake
        :param new_direction:
        :return:
        """
        directions = {"up" : (-1, 0), "down": (1, 0), "left": (0, -1), "right": (0, 1)}
        if new_direction in directions:
            self.grid.snake.change_direction(directions[new_direction])


