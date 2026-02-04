from domain import Question, Quiz


class QuizController:
    def __init__(self, repository):
        self.repository = repository


    def create_quiz(self, difficulty, number_of_questions, output_file):
        """
        Creates a quiz and saves it to a file.

        :param difficulty: Difficulty level.
        :param number_of_questions: Number of questions in the quiz.
        :param output_file: File to save the quiz.
        """
        easy_threshold = number_of_questions // 2
        easy_questions = self.repository.get_questions_by_difficulty("easy")
        medium_questions = self.repository.get_questions_by_difficulty("medium")
        hard_questions = self.repository.get_questions_by_difficulty("hard")

        if difficulty == "easy":
            questions = easy_questions[:easy_threshold] + medium_questions[:number_of_questions - easy_threshold]
        elif difficulty == "medium":
            questions = medium_questions[:easy_threshold] + hard_questions[:number_of_questions - easy_threshold]
        else:
            questions = hard_questions[:easy_threshold] + medium_questions[:number_of_questions - easy_threshold]

        quiz = Quiz(questions)
        with open(output_file, "w") as f:
            for question in quiz.questions:
                f.write(str(question) + "\n")

    def start_quiz(self, file):
        """
        Starts a quiz from a file.

        :param file: File containing the quiz.
        """
        questions = []
        with open(file, 'r') as f:
            for line in f:
                id, text, choices, correct_choice, difficulty = line.strip().split(';')
                choices = choices.split('|')
                questions.append(Question(int(id), text, choices, correct_choice, difficulty))

        questions.sort(key=lambda q: ["easy", "medium", "hard"].index(q.difficulty))
        score = 0

        for question in questions:
            print(f"{question.text}")
            for i, choice in enumerate(question.choices):
                print(f"{chr(65 + i)}. {choice}")
            user_answer = input("Your choice: ").lower()
            if user_answer == question.correct_choice:
                if question.difficulty == "easy":
                    score += 1
                elif question.difficulty == "medium":
                    score += 2
                else:
                    score += 3

        print(f"Quiz completed! Your score: {score}")
