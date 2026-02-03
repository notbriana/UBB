from DisciplineRepo.discipline_base_repo import DisciplineRepository
from domain.discipline import Discipline


class DisciplineTextFileRepository(DisciplineRepository):
    def __init__(self, file_path):
        super().__init__()
        self.__file_path = file_path

    def __read_all_from_file(self):
        try:
            with open(self.__file_path, "r") as f:
                self._entities.clear()
                for line in f:
                    parts = line.strip().split(",")
                    id_discipline = int(parts[0])
                    name = parts[1]
                    discipline = Discipline(id_discipline, name)
                    self._entities[id_discipline] = discipline
        except FileNotFoundError:
            self._entities = {}

    def __write_all_to_file(self):
        with open(self.__file_path, "w") as f:
            for id_discipline in self._entities:
                discipline = self._entities[id_discipline]
                f.write(f"{discipline.get_discipline_id()},{discipline.get_name()}\n")

    def add_entity(self, entity):
        self.__read_all_from_file()
        super().add_entity(entity)
        self.__write_all_to_file()

    def update_entity(self, entity):
        self.__read_all_from_file()
        super().update_entity(entity)
        self.__write_all_to_file()

    def delete_by_id(self, id_discipline):
        self.__read_all_from_file()
        super().delete_by_id(id_discipline)
        self.__write_all_to_file()

    def get_all(self):
        self.__read_all_from_file()
        return super().get_all()
