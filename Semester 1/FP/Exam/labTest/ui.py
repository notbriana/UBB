from service import BoardService
from exceptions import FileError, BoardError
from domain import Board
from repository import Repo


class UI:
    def __init__(self, board, repo, service):
        self.__board = board
        self.__repo = repo
        self.__service = service

    @staticmethod
    def get_input():
        """
        The function reads the input from the user
        :return:
        """
        command = input("> ")
        data = command.strip().split(' ')
        return data

    def start(self):
        # we need to get input from user => either to make a move or saving the current state of the board

        self.load_previous()
        print(self.__board)

        while True:
            if self.__service.full_board():
                print(self.__board)
                print("The board is full, Chaos won!")
                break
            data = self.get_input()
            if len(data) == 1 and data[0] == "save":
                self.save_board()
            elif len(data) < 3:
                print("Invalid input, must have at least 3 elements.")
            elif len(data) == 3:
                try:
                    self.move(data)
                    print("Moved successfully!")
                    if self.__service.check_if_won():
                        print(self.__board)
                        print("Congrats! Order won!")
                        break
                    computer = self.computer_move()
                    print(f"Computer moved to ({computer[0]}, {computer[1]}) with {computer[2]}.")
                    if self.__service.check_if_won():
                        print(self.__board)
                        print("Congrats! Order won!")
                        break


                    print(self.__board)
                except BoardError as e:
                    print(e)

    def save_board(self):
        """
        The function saves the board to a file
        :return:
        """
        self.__service.save()

    def move(self, data: list):
        """
        The function makes a move on the board
        :param data:
        :return:
        """
        self.__service.move(data[0], data[1], data[2])

    def computer_move(self):
        """
        The function makes the computer move
        :return:
        """
        return self.__service.computer_move()

    def load_previous(self):
        """
        Loads the previous saved game from the given file
        :return:
        """
        while True:
            choice = input("Do you want to load the previous game (Y/N)? > ")
            if choice == "Y":
                try:
                    self.__service.load('game.txt')
                    return
                except FileError as e:
                    print(e)
                    return
            elif choice == "N":
                return
            else:
                print("Wrong input!")


