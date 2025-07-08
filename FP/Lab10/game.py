import random
from board import Board

class Game:
    def __init__(self):
        self.board = Board()
        self.turn = Board.PLAYER

    def switch_turn(self):
        self.turn = Board.COMPUTER if self.turn == Board.PLAYER else Board.PLAYER

    def get_valid_locations(self):
        return [col for col in range(Board.columns) if self.board.is_valid_location(col)]

    def computer_move(self):
        valid_locations = self.get_valid_locations()
        for col in valid_locations:
            row, _ = self.board.drop_piece(col, Board.COMPUTER)
            if self.board.winning_move(Board.COMPUTER):
                return col
            self.board.board[row][col] = Board.empty

        for col in valid_locations:
            row, _ = self.board.drop_piece(col, Board.PLAYER)
            if self.board.winning_move(Board.PLAYER):
                self.board.board[row][col] = Board.COMPUTER
                return col
            self.board.board[row][col] = Board.empty

        return random.choice(valid_locations)

    def play(self, column):
        if self.board.is_valid_location(column):
            self.board.drop_piece(column, self.turn)
            if self.board.winning_move(self.turn):
                return True
            self.switch_turn()
        else:
            raise ValueError("Invalid move")
        return False