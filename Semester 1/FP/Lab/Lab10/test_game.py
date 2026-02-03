import unittest
from game import Game
from board import Board

class TestGame(unittest.TestCase):

    def setUp(self):
        self.game = Game()

    def test_switch_turn(self):
        self.assertEqual(self.game.turn, Board.PLAYER)
        self.game.switch_turn()
        self.assertEqual(self.game.turn, Board.COMPUTER)
        self.game.switch_turn()
        self.assertEqual(self.game.turn, Board.PLAYER)

    def test_get_valid_locations(self):
        self.assertEqual(self.game.get_valid_locations(), list(range(Board.columns)))
        for _ in range(Board.rows):
            self.game.board.drop_piece(0, Board.PLAYER)
        self.assertNotIn(0, self.game.get_valid_locations())

    def test_computer_move(self):
        self.game.board.drop_piece(0, Board.PLAYER)
        self.game.board.drop_piece(1, Board.PLAYER)
        self.game.board.drop_piece(2, Board.PLAYER)
        self.assertEqual(self.game.computer_move(), 3)

    def test_play(self):
        self.assertFalse(self.game.play(0))
        self.assertEqual(self.game.board.board[5][0], Board.PLAYER)
        self.assertEqual(self.game.turn, Board.COMPUTER)

if __name__ == '__main__':
    unittest.main()