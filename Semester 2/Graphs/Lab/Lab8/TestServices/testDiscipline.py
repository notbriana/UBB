import unittest
from unittest.mock import MagicMock
from domain.discipline import Discipline
from services.discipline_service import DisciplineService


class TestDisciplineService(unittest.TestCase):
    def setUp(self):
        self.mock_discipline_repo = MagicMock()
        self.discipline_service = DisciplineService(self.mock_discipline_repo)

    def test_add_discipline(self):
        discipline_id = 1
        name = "Mathematics"
        self.discipline_service.add_discipline(discipline_id, name)
        self.mock_discipline_repo.add_entity.assert_called_once_with(Discipline(discipline_id, name))

    def test_remove_discipline(self):
        discipline_id = 1
        discipline = Discipline(discipline_id, "Physics")
        self.mock_discipline_repo.find_by_id.return_value = discipline
        self.discipline_service.remove_discipline(discipline_id)
        self.mock_discipline_repo.delete_by_id.assert_called_once_with(discipline_id)

    def test_remove_discipline_not_found(self):
        self.mock_discipline_repo.find_by_id.return_value = None
        with self.assertRaises(ValueError) as context:
            self.discipline_service.remove_discipline(1)
        self.assertEqual(str(context.exception), "Discipline not found.")

    def test_update_discipline(self):
        discipline_id = 1
        new_name = "Advanced Physics"
        discipline = Discipline(discipline_id, "Physics")
        self.mock_discipline_repo.find_by_id.return_value = discipline
        self.discipline_service.update_discipline(discipline_id, new_name)
        self.mock_discipline_repo.update.assert_called_once_with(discipline_id, Discipline(discipline_id, new_name))

    def test_update_discipline_not_found(self):
        self.mock_discipline_repo.find_by_id.return_value = None
        with self.assertRaises(ValueError) as context:
            self.discipline_service.update_discipline(1, "Chemistry")
        self.assertEqual(str(context.exception), "Discipline not found.")

    def test_list_disciplines(self):
        disciplines = [Discipline(1, "Math"), Discipline(2, "Science")]
        self.mock_discipline_repo.get_all.return_value = disciplines
        result = self.discipline_service.list_disciplines()
        self.assertEqual(result, disciplines)
        self.mock_discipline_repo.get_all.assert_called_once()

    def test_search_disciplines(self):
        disciplines = [Discipline(1, "Math"), Discipline(2, "Physics")]
        self.mock_discipline_repo.get_all.return_value = disciplines
        result = self.discipline_service.search_disciplines("Math")
        self.assertEqual(result, [Discipline(1, "Math")])
        self.mock_discipline_repo.get_all.assert_called_once()

    def test_find_by_id(self):
        discipline_id = 1
        discipline = Discipline(discipline_id, "Biology")
        self.mock_discipline_repo.find_by_id.return_value = discipline
        result = self.discipline_service.find_by_id(discipline_id)
        self.assertEqual(result, discipline)
        self.mock_discipline_repo.find_by_id.assert_called_once_with(discipline_id)


if __name__ == "__main__":
    unittest.main()
