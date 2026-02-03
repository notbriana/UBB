class Student:
    def __init__(self, id_student, name, attendance_count, grade):
        self._id_student = id_student
        self._name = name
        self._attendance_count = attendance_count
        self._grade = grade

    def get_id(self):
        return self._id_student

    def get_name(self):
        return self._name

    def get_attendance_count(self):
        return self._attendance_count

    def get_grade(self):
        return self._grade

    def set_grade(self, value):
        self._grade = value

    
    def __str__(self):
        return f"{self._id_student},{self._name},{self._attendance_count},{self._grade}"
