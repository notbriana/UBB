from repository import QuestionRepository
from service import QuizController


class QuizUI:
    def __init__(self):
        self.repository = QuestionRepository()
        self.controller = QuizController(self.repository)

    def run(self):
        while True:
            command = input("Enter command: ").strip().split()
            if not command:
                continue

            action = command[0].lower()

            if action == "load":
                if len(command) != 2:
                    print("Usage: load <file>")
                    continue
                file = command[1]
                try:
                    self.repository.load_questions(file)
                    print("Questions loaded successfully.")
                except Exception as e:
                    print(str(e))

            elif action == "add":
                if len(command) != 8:
                    print("Usage: add <id> <text> <choice_a> <choice_b> <choice_c> <correct_choice> <difficulty>")
                    continue
                try:
                    id = int(command[1])
                    text = command[2]
                    choice_a = command[3]
                    choice_b = command[4]
                    choice_c = command[5]
                    correct_choice = command[6].lower()
                    difficulty = command[7].lower()
                    self.repository.add_question(id, text, choice_a, choice_b, choice_c, correct_choice, difficulty)
                    self.repository.save_questions('questions.txt')
                    print("Question added successfully.")
                except Exception as e:
                    print(f"Error: {str(e)}")

            elif action == "generate":
                if len(command) != 1:
                    print("Usage: generate")
                    continue
                self.repository.generate_random_questions()
                print("100 random questions generated.")

            elif action == "create":
                if len(command) != 4:
                    print("Usage: create <difficulty> <number_of_questions> <output_file>")
                    continue
                difficulty = command[1].lower()
                number_of_questions = int(command[2])
                output_file = command[3]
                self.controller.create_quiz(difficulty, number_of_questions, output_file)
                print(f"Quiz saved to {output_file}.")

            elif action == "start":
                if len(command) != 2:
                    print("Usage: start <file>")
                    continue
                file = command[1]
                self.controller.start_quiz(file)

            elif action == "exit":
                print("Goodbye!")
                break

            else:
                print("Invalid command. Please try again.")