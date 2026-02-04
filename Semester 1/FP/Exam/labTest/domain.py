from texttable import Texttable
from configuration import board_size


class Board:
    def __init__(self):
        #list of lists (each cell is represented by a list [row, column, symbol])
        self.__board = [[[i, j, '/'] for i in range(board_size)] for j in range(board_size)]
        self.symbols_placed = 0

    def symbols(self, row: int):
        """
        The function reads a row and searches along the board to retrieve a list of symbols for the specified row
        :param row: int
        :return: a list of symbols from the row, replacing '/' with space
        """
        list_symbols = []
        for i in range(board_size):
            if self.__board[i][row][2] == '/':
                list_symbols.append(' ')
            else:
                list_symbols.append(self.__board[i][row][2])
        return list_symbols

    def __str__(self):
        """
        The function returns a string representation of the board
        :return:
        """
        t = Texttable()
        header_row = ['/']
        for i in range(477):
            header_row.append(i)
        t.header(header_row)
        for j in range(board_size):
            t.add_row([j] + self.symbols(j))
        return t.draw()

    def board(self):
        """
        The function returns the board
        :return:
        """
        return self.__board

    def get_move(self, i: int, j: int):
        """
        The function returns the move at the given coordinates
        :param i: int, the column
        :param j: int, the row
        :return:
        """
        return self.__board[i][j]

    def move(self, i: int, j: int, symbol):
        """
        The function places a move on the board and counts the number of symbols existent
        :param i: int, the column
        :param j: int, the row
        :param symbol: str, symbol at (i,j)
        :return:
        """
        self.__board[i][j] = [i, j, symbol]

        if symbol != '/':
            self.symbols_placed += 1
