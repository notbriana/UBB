import unittest
from unittest.mock import MagicMock
from domain.student import Student
from services.student_service import StudentService

class TestStudentService(unittest.TestCase):

    def setUp(self):
        self.mock_student_repo = MagicMock()
        self.service = StudentService(self.mock_student_repo)

    def test_add_student(self):
        student_id = 1
        name = "John Doe"

        self.service.add_student(student_id, name)

        self.mock_student_repo.add_entity.assert_called_once_with(Student(student_id, name))

    def test_remove_student(self):
        student_id = 1

        self.mock_student_repo.find_by_id.return_value = Student(student_id, "John Doe")

        self.service.remove_student(student_id)

        self.mock_student_repo.delete_by_id.assert_called_once_with(student_id)

    def test_remove_student_not_found(self):
        student_id = 1

        self.mock_student_repo.find_by_id.return_value = None

        with self.assertRaises(ValueError):
            self.service.remove_student(student_id)

    def test_update_student(self):
        student_id = 1
        new_name = "Jane Doe"

        self.mock_student_repo.find_by_id.return_value = Student(student_id, "John Doe")

        self.service.update_student(student_id, new_name)

        self.mock_student_repo.update.assert_called_once_with(
            student_id, Student(student_id, new_name)
        )

    def test_update_student_not_found(self):
        student_id = 1
        new_name = "Jane Doe"

        self.mock_student_repo.find_by_id.return_value = None

        with self.assertRaises(ValueError):
            self.service.update_student(student_id, new_name)

    def test_list_students(self):
        self.service.list_students()

        self.mock_student_repo.get_all.assert_called_once()

    def test_search_students(self):
        search_term = "John"

        self.mock_student_repo.get_all.return_value = [
            Student(1, "John Doe"),
            Student(2, "Jane Smith")
        ]

        result = self.service.search_students(search_term)

        self.assertEqual(result, [Student(1, "John Doe")])

    def test_find_by_id(self):
        student_id = 1

        self.mock_student_repo.find_by_id.return_value = Student(student_id, "John Doe")

        result = self.service.find_by_id(student_id)

        self.assertEqual(result, Student(student_id, "John Doe"))

if __name__ == "__main__":
    unittest.main()
