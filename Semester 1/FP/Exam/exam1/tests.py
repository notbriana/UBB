import unittest
from unittest.mock import MagicMock
from service import Service
from domain import Student

class TestService(unittest.TestCase):
    def setUp(self):
        self.repo = MagicMock()
        self.service = Service(self.repo)

    def test_add_student(self):
        student = Student(1, "John Doe", 10, 8.5)
        self.repo.add = MagicMock()
        self.service.add(student.get_id(), student.get_name(), student.get_attendance_count(), student.get_grade())
        self.repo.add.assert_called_once_with(student)

    def test_get_all_students_sorted(self):
        student1 = Student(1, "John Doe", 10, 8.5)
        student2 = Student(2, "Jane Doe", 15, 9.0)
        self.repo.get_all.return_value = [student1, student2]
        sorted_students = self.service.get_all()
        self.assertEqual(sorted_students, [student2, student1])

    def test_give_bonus(self):
        student = Student(1, "John Doe", 10, 8.5)
        self.repo.get_all.return_value = [student]
        self.repo.update = MagicMock()
        self.service.give_bonus(5, 1.0)
        self.assertEqual(student.get_grade(), 9.5)
        self.repo.update.assert_called_once_with(student)

    def test_find_by_name(self):
        student1 = Student(1, "John Doe", 10, 8.5)
        student2 = Student(2, "Jane Doe", 15, 9.0)
        self.repo.get_all.return_value = [student1, student2]
        found_students = self.service.find_by_name("Jane")
        self.assertEqual(found_students, [student2])

if __name__ == '__main__':
    unittest.main()
