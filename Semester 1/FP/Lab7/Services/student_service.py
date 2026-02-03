from Domain.student import Student
import copy

class StudentService:

    def __init__(self, repo_students):
        self.__repo_students = repo_students
        self.__undo_stack = []

    def add_student(self, id_student, name, group):
        student = Student(id_student, name, group)
        old_repo = copy.deepcopy(self.__repo_students)
        self.__undo_stack.append(old_repo)
        self.__repo_students.add_entity(student)

    def show_all(self):
        return self.__repo_students.get_all()

    def filter_students_by_group(self, group):
        self.__undo_stack.append(copy.deepcopy(self.__repo_students))
        for student in self.__repo_students.get_all():
            if student.get_group() != group:
                self.__repo_students.delete_by_id(student.get_id_entity())
        
    def undo(self):
        if len(self.__undo_stack) > 0:
            print("Undo operation.")
            last_repo = self.__undo_stack.pop()
            self.__repo_students = last_repo
