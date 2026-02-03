import unittest
from unittest.mock import MagicMock
from domain.grade import Grade
from services.grade_service import GradeService

class TestGradeService(unittest.TestCase):

    def setUp(self):
        self.mock_grade_repo = MagicMock()
        self.mock_student_repo = MagicMock()
        self.mock_discipline_repo = MagicMock()

        self.service = GradeService(self.mock_grade_repo, self.mock_student_repo, self.mock_discipline_repo)

    def test_add_grade(self):
        discipline_id = 1
        student_id = 1
        grade_value = 9.5

        self.mock_discipline_repo.get_by_id.return_value = True
        self.mock_student_repo.get_by_id.return_value = True

        self.service.add_grade(discipline_id, student_id, grade_value)

        self.mock_grade_repo.add_entity.assert_called_once_with(Grade(discipline_id, student_id, grade_value))

    def test_add_grade_discipline_not_found(self):
        discipline_id = 1
        student_id = 1
        grade_value = 9.5

        self.mock_discipline_repo.get_by_id.return_value = None

        with self.assertRaises(ValueError):
            self.service.add_grade(discipline_id, student_id, grade_value)

    def test_add_grade_student_not_found(self):
        discipline_id = 1
        student_id = 1
        grade_value = 9.5

        self.mock_discipline_repo.get_by_id.return_value = True
        self.mock_student_repo.get_by_id.return_value = None

        with self.assertRaises(ValueError):
            self.service.add_grade(discipline_id, student_id, grade_value)

    def test_list_grades(self):
        self.service.list_grades()

        self.mock_grade_repo.get_all.assert_called_once()

    def test_remove_grades_by_student(self):
        student_id = 1
        grade1 = MagicMock()
        grade1.get_student_id.return_value = student_id
        grade2 = MagicMock()
        grade2.get_student_id.return_value = 2
        self.mock_grade_repo.get_all.return_value = [grade1, grade2]

        self.service.remove_grades_by_student(student_id)

        self.mock_grade_repo.delete_by_id.assert_called_once_with(grade1.get_discipline_id())

    def test_remove_grades_by_discipline(self):
        discipline_id = 1
        grade1 = MagicMock()
        grade1.get_discipline_id.return_value = discipline_id
        grade2 = MagicMock()
        grade2.get_discipline_id.return_value = 2
        self.mock_grade_repo.get_all.return_value = [grade1, grade2]

        self.service.remove_grades_by_discipline(discipline_id)

        self.mock_grade_repo.delete_by_id.assert_called_once_with(grade1.get_student_id())

if __name__ == "__main__":
    unittest.main()
