import unittest
from service import Service
from repository import TextFileRepo
from domain import Assignment

class TestService(unittest.TestCase):
    def setUp(self):
        self.repo = TextFileRepo("test_assignments.txt")
        self.service = Service(self.repo)

    def test_add_assignment(self):
        self.service.add_assignment(11, "John Doe", "This is a solution")
        assignment = self.repo.find_by_id(11)
        self.assertIsNotNone(assignment)
        self.assertEqual(assignment.get_student_name(), "John Doe")
        self.assertEqual(assignment.get_solution(), "This is a solution")

    def test_add_assignment_existing_id(self):
        self.service.add_assignment(1, "John Doe", "This is a solution")
        with self.assertRaises(ValueError):
            self.service.add_assignment(1, "Jane Doe", "Another solution")

    def test_add_assignment_short_name(self):
        with self.assertRaises(ValueError):
            self.service.add_assignment(12, "Jo", "This is a solution")

    def test_add_assignment_empty_solution(self):
        with self.assertRaises(ValueError):
            self.service.add_assignment(13, "John Doe", "")

    def test_get_all_assignments_increasing_order(self):
        self.service.add_assignment(14, "Alice", "Solution A")
        self.service.add_assignment(15, "Bob", "Solution B")
        assignments = self.service.get_all_assignments_increasing_order()
        self.assertEqual(assignments[0].get_id(), 1)
        self.assertEqual(assignments[1].get_id(), 2)
        self.assertEqual(assignments[-2].get_id(), 14)
        self.assertEqual(assignments[-1].get_id(), 15)

    def test_dishonesty_check(self):
        self.service.add_assignment(16, "Charlie", "Common words here")
        self.service.add_assignment(17, "Dave", "Common words here too")
        pairs = self.service.dishonesty_check()
        self.assertTrue(len(pairs) > 0)
        self.assertEqual(pairs[0][0].get_id(), 16)
        self.assertEqual(pairs[0][1].get_id(), 17)

if __name__ == '__main__':
    unittest.main()