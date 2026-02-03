from domain import Student


class Service:
    def __init__(self, repo):
        self._repo = repo

    def repo(self):
        return self._repo

    def add(self, id, name, attendance_count, grade):
        student = Student(id, name, attendance_count, grade)
        try:
            self._repo.add(student)
        except ValueError:
            raise

    def get_all(self):
        students = self._repo.get_all()
        students_sorted = sorted(students, key=lambda student: (-student.get_grade(), student.get_name()))
        return students_sorted

    def give_bonus(self, p, b):
        students = self._repo.get_all()
        for student in students:
            if student.get_attendance_count() >= p:
                student.set_grade(student.get_grade() + b)

                if student.get_grade() > 10:
                    student.set_grade(10)
                self._repo.update(student)

    def find_by_name(self, substring):
        students = self._repo.get_all()
        filtered_students = [student for student in students if substring.lower() in student.get_name().lower()]
        sorted_students = sorted(filtered_students, key=lambda student: student.get_name())
        return sorted_students
