from GradeRepo.grade_base_repo import GradeRepository
from domain.grade import Grade


class GradeTextFileRepository(GradeRepository):
    def __init__(self, file_path):
        super().__init__()
        self.__file_path = file_path

    def __read_all_from_file(self):
        try:
            with open(self.__file_path, "r") as f:
                self._entities.clear()
                for line in f:
                    parts = line.strip().split(",")
                    discipline_id = int(parts[0])
                    student_id = int(parts[1])
                    grade_value = float(parts[2])
                    grade = Grade(discipline_id, student_id, grade_value)
                    self._entities[(discipline_id, student_id)] = grade
        except FileNotFoundError:
            self._entities = {}

    def __write_all_to_file(self):
        with open(self.__file_path, "w") as f:
            for grade in self._entities.values():
                f.write(f"{grade.get_discipline_id()},{grade.get_student_id()},{grade.get_grade_value()}\n")

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
