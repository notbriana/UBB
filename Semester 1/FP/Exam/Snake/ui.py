
import os
from service import SnakeGame

class UI:
    def __init__(self, grid_size=8, apples_count=3):
        self.game = SnakeGame(grid_size, apples_count)
        self.commands = {"w": "up", "s": "down", "a": "left", "d": "right"}

    def clear_screen(self):
        os.system('cls' if os.name == 'nt' else 'clear')

    def run(self):
        while not self.game.game_over:
            self.clear_screen()
            self.game.grid.update_grid()
            user_input = input("Enter command: ").strip().lower()
            self.handle_command(user_input)
            self.game.update()
        print("GAME OVER")

    def handle_command(self, command):
        if command.startswith("move"):
            parts = command.split()
            steps = int(parts[1]) if len(parts) > 1 else 1
            self.game.update(steps)
        elif command in self.commands:
            new_direction = self.commands[command]
            if self.is_valid_direction_change(new_direction):
                self.game.change_snake_direction(new_direction)
            else:
                print("Invalid direction change!")
        else:
            print("Invalid command!")

    def is_valid_direction_change(self, new_direction):
        current_direction = self.game.grid.snake.direction
        directions = {"up": (-1, 0), "down": (1, 0), "left": (0, -1), "right": (0, 1)}
        new_dir_vector = directions[new_direction]
        if (current_direction[0] + new_dir_vector[0], current_direction[1] + new_dir_vector[1]) == (0, 0):
            return False
        return True