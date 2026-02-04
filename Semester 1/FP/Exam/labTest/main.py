from domain import Board
from repository import Repo
from service import BoardService
from ui import UI

def main():
    board = Board()
    repo = Repo(board)
    service = BoardService(board, repo)
    ui = UI(board, repo, service)
    ui.start()

if __name__ == "__main__":
    main()