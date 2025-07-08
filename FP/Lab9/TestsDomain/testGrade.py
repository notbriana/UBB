import unittest

from domain.grade import Grade


class TestGrade(unittest.TestCase):
    def test_valid_grade_initialization(self):
        grade = Grade(discipline_id=1, student_id=2, grade_value=9.5)
        self.assertEqual(grade.get_discipline_id(), 1)
        self.assertEqual(grade.get_student_id(), 2)
        self.assertEqual(grade.get_grade_value(), 9.5)

    def test_invalid_discipline_id(self):
        with self.assertRaises(ValueError):
            Grade(discipline_id=-1, student_id=2, grade_value=9.5)
        with self.assertRaises(ValueError):
            Grade(discipline_id="a", student_id=2, grade_value=9.5)

    def test_invalid_student_id(self):
        with self.assertRaises(ValueError):
            Grade(discipline_id=1, student_id=-2, grade_value=9.5)
        with self.assertRaises(ValueError):
            Grade(discipline_id=1, student_id="b", grade_value=9.5)

    def test_invalid_grade_value(self):
        with self.assertRaises(ValueError):
            Grade(discipline_id=1, student_id=2, grade_value=11.0)
        with self.assertRaises(ValueError):
            Grade(discipline_id=1, student_id=2, grade_value=0.0)
        with self.assertRaises(ValueError):
            Grade(discipline_id=1, student_id=2, grade_value="invalid")

    def test_setters(self):
        grade = Grade(discipline_id=1, student_id=2, grade_value=5.0)
        grade.set_discipline_id(3)
        grade.set_student_id(4)
        grade.set_grade_value(8.0)
        self.assertEqual(grade.get_discipline_id(), 3)
        self.assertEqual(grade.get_student_id(), 4)
        self.assertEqual(grade.get_grade_value(), 8.0)

    def test_repr(self):
        grade = Grade(discipline_id=1, student_id=2, grade_value=8.0)
        self.assertEqual(repr(grade), "Grade(DisciplineID=1, StudentID=2, Value=8.0)")


if __name__ == "__main__":
    unittest.main()
