from domain import Board
from random import randint, choice
from exceptions import BoardError
from repository import Repo
from configuration import board_size, number_of_symbols


class BoardService:
    def __init__(self, board: Board, repo: Repo):
        self.__board = board
        self.__repo = repo

    def move(self, i: int, j: int, symbol: str):
        """
        The function places a move on the board at the given coordinates
        :param i: int, the column index
        :param j: int, the row index
        :param symbol: str, the symbol to place
        :return:
        """
        #if the coordinates aren't integers, raise a BoardError
        try:
            i = int(i)
            j = int(j)
        except ValueError as error:
            raise BoardError("Invalid literal, coordinates must be ints.")

        #if the coordinates are out of bounds, raise a BoardError
        if i < 0 or i > board_size - 1 or j < 0 or j > board_size - 1:
            raise BoardError("The coordinates should be within bounds.")

        #if the symbol isn't X, 0 or /, raise a BoardError
        if symbol != "O" and symbol != "X" and symbol != '/':
            raise BoardError("Invalid symbol!")

        #if the space is already occupied, raise a BoardError (u can't place a symbol on an occupied space)
        a = self.__board.get_move(i, j)
        if a[2] != '/':
            raise BoardError("Space already occupied!")

        self.__board.move(i, j, symbol)

    def computer_move(self):
        """
        The function makes the computer move.
        If there is a possible win for order, block it (put x if the player puts 0s and 0 if the player puts Xs). Else make a random but valid move.

        :return:
        """
        if self.possible_win() is not None:
            i, j, s = self.possible_win()
            if s == "X":

                self.move(i, j, "O")
                return [i, j, "O"]
            else:
                self.move(i, j, "X")
                return [i, j, "X"]

        while True:
            try:
                i = randint(0, board_size)
                j = randint(0, board_size)
                symbol = choice(["O", "X"])
                self.move(i, j, symbol)
                return [i, j, symbol]
            except BoardError:
                pass

    def check_if_won(self):
        """
        The function checks if the game is won
        :return:
        """
        for i in range(board_size):
            for j in range(board_size):
                symbol = self.__board.get_move(i, j)[2]
                if symbol != '/' and self.check_consecutive(i, j, symbol):
                    return True
        return False

    def check_consecutive(self, row: int, col: int, symbol: str):
        """
        The function checks if there are enough consecutive symbols on the board
        :param row: int, the column index
        :param col: int, the row index
        :param symbol: str, the symbol index
        :return:
        """
        #the directions in which the function will search for consecutive symbols(up, down, left, right,...)
        directions = [(-1, 0), (1, 0), (0, -1), (0, 1), (-1, -1), (-1, 1), (1, -1), (1, 1)]

        for direction_row, direction_column in directions:
            counter = 1
            for step in range(1, number_of_symbols):

                new_row, new_column = row + step * direction_row, col + step * direction_column

                if 0 <= new_row < board_size and 0 <= new_column < board_size and self.__board.get_move(new_row, new_column)[2] == symbol:
                    counter += 1
                else:
                    break
            if counter == number_of_symbols:
                return True
        return False

    def possible_win(self):
        """
        The function checks if there is a possible win, for each cell of the board
        :return:
        """
        for i in range(board_size):
            for j in range(board_size):
                for s in ["X", "O"]:
                    if self.__board.get_move(i, j)[2] == '/':
                        self.move(i, j, s)
                        if self.check_if_won():
                            self.__board.move(i, j, '/')
                            return [i, j, s]
                        self.__board.move(i, j, '/')
        return None

    def full_board(self):
        """
        The function checks if the board is full
        :return:
        """
        if self.__board.symbols_placed == board_size * board_size:
            return True
        return False

    def load(self, filename):
        """
        The function loads a game from a file
        :param filename: the file where the game is saved
        :return:
        """
        self.__repo.load(filename)

    def save(self, filename='game.txt'):
        """
        The function saves a game to a file
        :param filename: game.txt, where we save the game
        :return:
        """
        self.__repo.save(filename)


