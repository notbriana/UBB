import unittest
from board import Board

class TestBoard(unittest.TestCase):

    def setUp(self):
        self.board = Board()

    def test_drop_piece(self):
        self.board.drop_piece(0, Board.PLAYER)
        self.assertEqual(self.board.board[5][0], Board.PLAYER)

    def test_is_valid_location(self):
        self.assertTrue(self.board.is_valid_location(0))
        self.board.drop_piece(0, Board.PLAYER)
        self.assertTrue(self.board.is_valid_location(0))
        for _ in range(5):
            self.board.drop_piece(0, Board.PLAYER)
        self.assertFalse(self.board.is_valid_location(0))

    def test_winning_move_horizontal(self):
        for col in range(4):
            self.board.drop_piece(col, Board.PLAYER)
        self.assertTrue(self.board.winning_move(Board.PLAYER))

    def test_winning_move_vertical(self):
        for _ in range(4):
            self.board.drop_piece(0, Board.PLAYER)
        self.assertTrue(self.board.winning_move(Board.PLAYER))

    def test_winning_move_diagonal_positive(self):
        for i in range(4):
            for j in range(i):
                self.board.drop_piece(i, Board.COMPUTER)
            self.board.drop_piece(i, Board.PLAYER)
        self.assertTrue(self.board.winning_move(Board.PLAYER))

    def test_winning_move_diagonal_negative(self):
        for i in range(4):
            for j in range(i):
                self.board.drop_piece(3 - i, Board.COMPUTER)
            self.board.drop_piece(3 - i, Board.PLAYER)
        self.assertTrue(self.board.winning_move(Board.PLAYER))

if __name__ == '__main__':
    unittest.main()