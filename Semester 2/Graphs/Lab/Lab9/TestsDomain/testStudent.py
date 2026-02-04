import unittest

from domain.student import Student


class TestStudent(unittest.TestCase):
    def test_valid_student_initialization(self):
        student = Student(student_id=1, name="John Doe")
        self.assertEqual(student.get_student_id(), 1)
        self.assertEqual(student.get_name(), "John Doe")

    def test_invalid_student_id(self):
        with self.assertRaises(ValueError):
            Student(student_id=-1, name="John Doe")
        with self.assertRaises(ValueError):
            Student(student_id="a", name="John Doe")

    def test_invalid_student_name(self):
        with self.assertRaises(ValueError):
            Student(student_id=1, name="")
        with self.assertRaises(ValueError):
            Student(student_id=1, name=123)

    def test_setters(self):
        student = Student(student_id=1, name="John Doe")
        student.set_student_id(2)
        student.set_name("Jane Doe")
        self.assertEqual(student.get_student_id(), 2)
        self.assertEqual(student.get_name(), "Jane Doe")

    def test_strip_name(self):
        student = Student(student_id=1, name="  John Doe  ")
        self.assertEqual(student.get_name(), "John Doe")

    def test_repr(self):
        student = Student(student_id=1, name="Jane Doe")
        self.assertEqual(repr(student), "Student(ID=1, Name=Jane Doe)")

if __name__ == "__main__":
    unittest.main()
