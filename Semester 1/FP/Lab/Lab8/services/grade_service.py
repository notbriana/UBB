from domain.grade import Grade

class GradeService:
    def __init__(self, grade_repo, student_repo, discipline_repo, undo_services):
        self.__grade_repo = grade_repo
        self.__student_repo = student_repo
        self.__discipline_repo = discipline_repo
        self.__undo_services = undo_services

    def add_grade(self, discipline_id, student_id, grade_value):
        if not self.__discipline_repo.get_by_id(discipline_id):
            raise ValueError("Discipline not found.")
        if not self.__student_repo.get_by_id(student_id):
            raise ValueError("Student not found.")
        grade = Grade(discipline_id, student_id, grade_value)
        self.__grade_repo.add_entity(grade)

    def list_grades(self):
        return self.__grade_repo.get_all()

    def remove_grades_by_student(self, student_id):
        grades = self.__grade_repo.get_all()
        for grade in grades:
            if grade.get_student_id() == student_id:
                self.__grade_repo.delete_by_id(grade.get_discipline_id())

    def remove_grades_by_discipline(self, discipline_id):
        grades = self.__grade_repo.get_all()
        for grade in grades:
            if grade.get_discipline_id() == discipline_id:
                self.__grade_repo.delete_by_id(grade.get_student_id())


