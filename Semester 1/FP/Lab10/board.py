class Board:
    rows = 6
    columns = 7
    empty = 0
    PLAYER = 1
    COMPUTER = 2

    def __init__(self):
        self.board = [[self.empty for _ in range(self.columns)] for _ in range(self.rows)]

    def drop_piece(self, column, piece):
        for row in reversed(range(self.rows)):
            if self.board[row][column] == self.empty:
                self.board[row][column] = piece
                return row, column
        raise ValueError("Column is full")

    def is_valid_location(self, column):
        return self.board[0][column] == self.empty

    def winning_move(self, piece):
        for row in range(self.rows):
            for col in range(self.columns - 3):
                if all(self.board[row][col + i] == piece for i in range(4)):
                    return True

        for col in range(self.columns):
            for row in range(self.rows - 3):
                if all(self.board[row + i][col] == piece for i in range(4)):
                    return True

        for row in range(self.rows - 3):
            for col in range(self.columns - 3):
                if all(self.board[row + i][col + i] == piece for i in range(4)):
                    return True

        for row in range(3, self.rows):
            for col in range(self.columns - 3):
                if all(self.board[row - i][col + i] == piece for i in range(4)):
                    return True

        return False

    def print_board(self):
        for row in self.board:
            print(row)