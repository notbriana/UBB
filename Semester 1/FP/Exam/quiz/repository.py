import random

from domain import Question


class QuestionRepository:
    def __init__(self):
        self.questions = []

    def load_questions(self, file):
        with open(file, 'r') as f:
            for line in f:
                id, text, choices, correct_choice, difficulty = line.strip().split(';')
                choices = choices.split('|')
                self.questions.append(Question(int(id), text, choices, correct_choice, difficulty))

    def add_question(self, id, text, choice_a, choice_b, choice_c, correct_choice, difficulty):
        choices = [choice_a, choice_b, choice_c]
        self.questions.append(Question(id, text, choices, correct_choice, difficulty))

    def generate_random_questions(self):
        difficulties = ['easy', 'medium', 'hard']
        for i in range(100):
            id = i + 1
            text = f"Sample question {id}"
            choices = [f"Choice A{id}", f"Choice B{id}", f"Choice C{id}"]
            correct_choice = random.choice(['a', 'b', 'c'])
            difficulty = random.choice(difficulties)
            self.questions.append(Question(id, text, choices, correct_choice, difficulty))
        self.save_questions('questions.txt')

    def save_questions(self, file):
        with open(file, 'w') as f:
            for question in self.questions:
                choices = '|'.join(question.choices)
                f.write(f"{question.id};{question.text};{choices};{question.correct_choice};{question.difficulty}\n")

    def get_questions_by_difficulty(self, difficulty):
        filtered = [question for question in self.questions if question.difficulty == difficulty]
        return filtered


