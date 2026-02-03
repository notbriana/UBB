class GameState:

    def __init__(self, sentence, scrambled_sentence):
        self.sentence = sentence
        self.scrambled_sentence = scrambled_sentence
        self.score = len(sentence.replace(" ", ""))
        self.history = []

    def swap_letters(self, word1_idx, letter1_idx, word2_idx, letter2_idx):
        words = self.scrambled_sentence.split()

        if word1_idx == word2_idx:
            word = list(words[word1_idx])
            word[letter1_idx], word[letter2_idx] = word[letter2_idx], word[letter1_idx]
            words[word1_idx] = ''.join(word)
        else:
            word1 = list(words[word1_idx])
            word2 = list(words[word2_idx])
            print(len(word2))
            print(letter2_idx)
            print(word2)
            word1[letter1_idx], word2[letter2_idx] = word2[letter2_idx], word1[letter1_idx]
            words[word1_idx] = ''.join(word1)
            words[word2_idx] = ''.join(word2)

        self.scrambled_sentence = ''.join(words)
        self.history.append((word1_idx, letter1_idx, word2_idx, letter2_idx))
        self.update_score()

    def undo_last_swap(self):
        if len(self.history) == 0:
            return

        last_swap = self.history.pop()
        self.swap_letters(last_swap[0], last_swap[1], last_swap[2], last_swap[3])
        self.history.pop()

    def update_score(self):
        self.score -= 1



