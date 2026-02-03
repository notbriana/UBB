from Domain.student import Student
from Repositories.student_base_repo import Repository

class StudentTextFileRepository(Repository):
    def __init__(self, file_path):
        super().__init__()
        self.__file_path = file_path

    def __read_all_from_file(self):
        try:
            with open(self.__file_path, "r") as f:
                self._entities.clear()
                for line in f:
                    parts = line.strip().split(",")
                    if len(parts) < 3:
                        continue
                    try:
                        id_student = int(parts[0])
                        name = parts[1]
                        group = int(parts[2])
                        student = Student(id_student, name, group)
                        self._entities[id_student] = student
                    except ValueError:
                        print(f"Skipping invalid line: {line.strip()}")
        except FileNotFoundError:
            self._entities = {}

    def __write_all_to_file(self):
        with open(self.__file_path, "w") as f:
            for student in self._entities.values():
                f.write(f"{student.get_id_student()},{student.get_name()},{student.get_group()}\n")

    def add_entity(self, entity):
        self.__read_all_from_file()
        super().add_entity(entity)
        self.__write_all_to_file()

    def update_entity(self, entity):
        self.__read_all_from_file()
        super().update_entity(entity)
        self.__write_all_to_file()

    def delete_by_id(self, id_entity):
        self.__read_all_from_file()
        super().delete_by_id(id_entity)
        self.__write_all_to_file()

    def get_all(self):
        self.__read_all_from_file()
        return super().get_all()
