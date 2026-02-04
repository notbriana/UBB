import unittest
from repository import QuestionRepository
from service import QuizController
from domain import Question, Quiz

class TestQuizService(unittest.TestCase):
    def setUp(self):
        self.repo = QuestionRepository()
        self.service = QuizController(self.repo)
        self.repo.add_question(1, "What is the capital of France?", "Paris", "London", "Berlin", "a", "easy")
        self.repo.add_question(2, "What is the capital of Germany?", "Paris", "London", "Berlin", "c", "easy")
        self.repo.add_question(3, "What is the capital of Italy?", "Rome", "Milan", "Naples", "a", "easy")

    def test_create_quiz(self):
        self.service.create_quiz("easy", 1, "test_quiz.txt")
        with open("test_quiz.txt", "r") as f:
            lines = f.readlines()
        self.assertEqual(len(lines), 0)

    def test_start_quiz(self):
        with open("test_quiz.txt", "w") as f:
            f.write("1;Sample question?;A|B|C;a;easy\n")
        self.service.start_quiz("test_quiz.txt")
        # This test will require user input, so it's better to mock input for automated testing

if __name__ == '__main__':
    unittest.main()