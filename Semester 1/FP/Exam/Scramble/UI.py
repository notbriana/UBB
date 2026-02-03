from domain import GameState


class UI:
    def __init__(self, service, repository):
        self.service = service
        self.repository = repository

    def main(self):
        sentences = self.repository.load_sentences('sentences.txt')
        original_sentence = self.repository.get_random_sentence(sentences)
        scrambled_sentence = self.service.scrambled_sentence(original_sentence)
        game_state = GameState(original_sentence, scrambled_sentence)

        print("Scrambled Sentence:", scrambled_sentence)

        while game_state.score > 0 and not self.service.is_correct_order(game_state.sentence, game_state.scrambled_sentence):
            print("\nCurrent Scrambled Sentence:", game_state.scrambled_sentence)
            print(f"Score: {game_state.score}")
            user_input = input("Enter swap command (swap word1_idx letter1_idx - word2_idx letter2_idx) or 'undo' to undo last swap: ")

            if user_input.lower() == 'undo':
                game_state.undo_last_swap()
            else:
                try:
                    parts = user_input.split()
                    if parts[0].lower() == 'swap' and parts[3] == '-':
                        word1_idx, letter1_idx, word2_idx, letter2_idx = map(int, [parts[1], parts[2], parts[4], parts[5]])
                        game_state.swap_letters(word1_idx, letter1_idx, word2_idx, letter2_idx)
                    else:
                        print("Invalid input. Please enter the command in the correct format.")
                except ValueError:
                    print("Invalid input. Please enter the command in the correct format.")

        if self.service.is_correct_order(game_state.sentence, game_state.scrambled_sentence):
            print("Congratulations! You've unscrambled the sentence.")
        else:
            print("Game over! Your score is 0.")