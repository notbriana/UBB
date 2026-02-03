from game import Game

def print_board(board):
    for row in board.board:
        print(' '.join(str(cell) for cell in row))

def main():
    game = Game()
    game_over = False

    while not game_over:
        print_board(game.board)
        if game.turn == game.board.PLAYER:
            column = int(input("Player 1 Make your Selection (0-6):"))
            try:
                game_over = game.play(column)
            except ValueError as e:
                print(e)
        else:
            column = game.computer_move()
            print(f"Computer selects column {column}")
            game_over = game.play(column)

        if game_over:
            print_board(game.board)
            print(f"Player {game.turn} wins!")

if __name__ == "__main__":
    main()