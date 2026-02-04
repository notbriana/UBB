# ui.py
class InterstellarUI:
    def __init__(self, service):
        self.service = service

    def display_grid(self):
        self.service.game.grid.display_grid()

    def start_game(self):
        print("Welcome to Interstellar!")
        print("The Endeavour is represented by 'E'.")
        print("The Blingons are represented by 'B'.")
        print("The stars are represented by '*'.")

        while self.service.game.running:
            self.display_grid()
            command = input("Enter command: ")
            result = self.service.process_command(command)
            print(result)