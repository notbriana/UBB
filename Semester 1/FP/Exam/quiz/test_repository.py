import unittest
from repository import QuestionRepository
from domain import Question, Quiz

class TestQuestionsRepository(unittest.TestCase):
    def setUp(self):
        self.repo = QuestionRepository()
        self.repo.add_question(1, "What is the capital of France?", "Paris", "London", "Berlin", "a", "easy")

    def test_load_questions(self):
        self.repo.load_questions('questions.txt')
        self.assertGreater(len(self.repo.questions), 0)

    def test_add_question(self):
        self.repo.add_question(2, "What is the capital of Germany?", "Paris", "London", "Berlin", "c", "easy")
        self.assertEqual(len(self.repo.questions), 2)

    def test_get_questions_by_difficulty(self):
        easy_questions = self.repo.get_questions_by_difficulty("easy")
        self.assertEqual(len(easy_questions), 1)

if __name__ == "__main__":
    unittest.main()