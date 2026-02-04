class Question:

    def __init__(self, id, text, choices, correct_choice, difficulty):
        self.id = id
        self.text = text
        self.choices = choices
        self.correct_choice = correct_choice
        self.difficulty = difficulty

    def id(self):
        return self.id

    def text(self):
        return self.text

    def choices(self):
        return self.choices

    def difficulty(self):
        return self.difficulty

    def correct_choice(self):
        return self.correct_choice


    def __str__(self):
        return f"{self.id}; {self.text}; {'|'.join(self.choices)};{self.correct_choice};{self.difficulty}"


class Quiz:
    def __init__(self, questions):
        self.questions = questions


