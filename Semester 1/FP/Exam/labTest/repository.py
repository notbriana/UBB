from domain import Board
from exceptions import FileError, BoardError
from configuration import board_size

class Repo:
    def __init__(self, board: Board):
        self.__board = board

    def load(self, filename):
        """
        This is where we load a game
        :param filename: from where we load a game
        :return:
        """
        try:
            with open(filename, 'r') as file:
                if file.readable() and len(file.read()) == 0:
                    raise FileError("File is empty!")
                file.seek(0)
                for line in file:
                    data = line.strip().split(',')
                    try:
                        i = int(data[0])
                        j = int(data[1])
                        symbol = data[2]
                        self.__board.move(i, j, symbol)
                    except BoardError as err:
                        raise FileError(str(err))
        except FileNotFoundError:
            raise FileError("File doesn't exist.")

    def save(self, filename='game.txt'):
        try:
            with open(filename, 'w') as file:
                for i in range(board_size):
                    for j in range(board_size):
                        move = self.__board.get_move(i, j)
                        file.write(f"{move[0]},{move[1]},{move[2]},\n")
        except Exception as err:
            raise FileError(f"Error saving to file: {err}")