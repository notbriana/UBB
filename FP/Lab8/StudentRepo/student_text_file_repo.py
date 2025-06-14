from StudentRepo.student_base_repo import StudentRepository
from domain.student import Student


class StudentTextFileRepository(StudentRepository):
    def __init__(self, file_path):
        super().__init__()
        self.__file_path = file_path

    def __read_all_from_file(self):
        try:
            with open(self.__file_path, "r") as f:
                self._entities.clear()
                for line in f:
                    parts = line.strip().split(",")
                    student_id = int(parts[0])
                    name = parts[1]
                    student = Student(student_id, name)
                    self._entities[student_id] = student
        except FileNotFoundError:
            self._entities = {}

    def __write_all_to_file(self):
        with open(self.__file_path, "w") as f:
            for student in self._entities.values():
                f.write(f"{student.get_student_id()},{student.get_name()}\n")

    def add_entity(self, entity):
        self.__read_all_from_file()
        super().add_entity(entity)
        self.__write_all_to_file()

    def update_entity(self, entity):
        self.__read_all_from_file()
        super().update_entity(entity)
        self.__write_all_to_file()

    def delete_by_id(self, student_id):
        self.__read_all_from_file()
        super().delete_by_id(student_id)
        self.__write_all_to_file()

    def get_all(self):
        self.__read_all_from_file()
        return super().get_all()
