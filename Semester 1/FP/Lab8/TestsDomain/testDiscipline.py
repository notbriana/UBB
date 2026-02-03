import unittest
from domain.discipline import Discipline


class TestDiscipline(unittest.TestCase):
    def test_valid_discipline_initialization(self):
        discipline = Discipline(discipline_id=1, name="Mathematics")
        self.assertEqual(discipline.get_discipline_id(), 1)
        self.assertEqual(discipline.get_name(), "Mathematics")

    def test_invalid_discipline_id(self):
        with self.assertRaises(ValueError):
            Discipline(discipline_id=-1, name="Mathematics")
        with self.assertRaises(ValueError):
            Discipline(discipline_id="a", name="Mathematics")

    def test_invalid_discipline_name(self):
        with self.assertRaises(ValueError):
            Discipline(discipline_id=1, name="")
        with self.assertRaises(ValueError):
            Discipline(discipline_id=1, name=123)

    def test_setters(self):
        discipline = Discipline(discipline_id=1, name="History")
        discipline.set_id(2)
        discipline.set_name("Geography")
        self.assertEqual(discipline.get_discipline_id(), 2)
        self.assertEqual(discipline.get_name(), "Geography")

    def test_repr(self):
        discipline = Discipline(discipline_id=1, name="Physics")
        self.assertEqual(repr(discipline), "Discipline(ID=1, Name=Physics)")

if __name__ == "__main__":
    unittest.main()
