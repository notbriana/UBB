'''
student_repo=binary
discipline_repo=binary
grade_repo=binary
'''

from DisciplineRepo.discipline_base_repo import DisciplineRepository
from GradeRepo.grade_base_repo import GradeRepository
from StudentRepo.student_base_repo import StudentRepository
from DisciplineRepo.discipline_text_file_repo import DisciplineTextFileRepository
from GradeRepo.grade_text_file_repo import GradeTextFileRepository
from StudentRepo.student_text_file_repo import StudentTextFileRepository
from DisciplineRepo.discipline_binary_file_repo import DisciplineBinaryFileRepository
from GradeRepo.grade_binary_file_repo import GradeBinaryFileRepository
from StudentRepo.student_binary_file_repo import StudentBinaryFileRepository

class Settings:
    def __init__(self, filename="src/settings.properties"):
        self.__filename = filename
        self.__settings = {}
        self.load_settings()
    
    def load_settings(self):
        with open(self.__filename, "r") as f:
            for line in f:
                parts = line.strip().split("=")
                key = parts[0].strip()
                value = parts[1].strip()
                self.__settings[key] = value
    
    def get_student_repo(self):
        if self.__settings["student_repo"] == "text":
            return StudentTextFileRepository("students.txt")
        elif self.__settings["student_repo"] == "binary":
            return StudentBinaryFileRepository("students.bin")
        elif self.__settings["student_repo"] == "inmemory":
            return StudentRepository()
    
    def get_discipline_repo(self):
        if self.__settings["discipline_repo"] == "text":
            return DisciplineTextFileRepository("disciplines.txt")
        elif self.__settings["discipline_repo"] == "binary":
            return DisciplineBinaryFileRepository("disciplines.bin")
        elif self.__settings["discipline_repo"] == "inmemory":
            return DisciplineRepository()
    
    def get_grade_repo(self):
        if self.__settings["grade_repo"] == "text":
            return GradeTextFileRepository("grades.txt")
        elif self.__settings["grade_repo"] == "binary":
            return GradeBinaryFileRepository("grades.bin")
        elif self.__settings["grade_repo"] == "inmemory":
            return GradeRepository()