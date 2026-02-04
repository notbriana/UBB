# main.py
from domain import Game
from service import InterstellarService
from ui import InterstellarUI

if __name__ == '__main__':
    game = Game()
    service = InterstellarService(game)
    ui = InterstellarUI(service)
    ui.start_game()