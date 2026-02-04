import pickle

from GradeRepo.grade_base_repo import GradeRepository


class GradeBinaryFileRepository(GradeRepository):
    def __init__(self, file_path):
        super().__init__()
        self.__file_path = file_path

    def __read_all_from_file(self):
        try:
            with open(self.__file_path, "rb") as f:
                self._entities = pickle.load(f)
        except FileNotFoundError:
            self._entities = {}

    def __write_all_to_file(self):
        with open(self.__file_path, "wb") as f:
            pickle.dump(self._entities, f)

    def add_entity(self, entity):
        self.__read_all_from_file()
        super().add_entity(entity)
        self.__write_all_to_file()

    def update_entity(self, entity):
        self.__read_all_from_file()
        super().update_entity(entity)
        self.__write_all_to_file()

    def delete_by_id(self, discipline_id, student_id):
        self.__read_all_from_file()
        super().delete_by_id(discipline_id, student_id)
        self.__write_all_to_file()

    def get_all(self):
        self.__read_all_from_file()
        return super().get_all()
