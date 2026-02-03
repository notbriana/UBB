import random


class Repository:
    def __init__(self):
        pass

    def load_sentences(self, file):
        try:
            with open(file, 'r') as f:
                sentences = f.readlines()
            return [sentence.strip() for sentence in sentences]
        except IOError as e:
            raise ValueError(f'An error occurred - {e}')

    def get_random_sentence(self, sentences):
        return random.choice(sentences)