import random

class Service:
    def __init__(self):
        pass


    def scrambled_sentence(self, sentence):
        words = sentence.split()
        all_letters = []
        for word in words:
            if len(word) > 3:
                all_letters.extend(word[1:-1])
        random.shuffle(all_letters)

        scrambled_words = []
        letter_idx = 0
        for word in words:
            if len(word) > 3:
                middle = ''.join(all_letters[letter_idx:letter_idx + len(word) - 2])
                scrambled_word = word[0] + middle + word[-1]
                letter_idx += len(word) - 2
            else:
                scrambled_word = word

            scrambled_words.append(scrambled_word)

        return ' '.join(scrambled_words)

    def is_correct_order(self, sentence, scrambled_sentence):
        return sentence == scrambled_sentence