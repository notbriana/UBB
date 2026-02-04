class Grade:
    def __init__(self, discipline_id: int, student_id: int, grade_value: float):
        self.__discipline_id = discipline_id
        self.__student_id = student_id
        self.__grade_value = grade_value

    def get_discipline_id(self):
        return self.__discipline_id

    def set_discipline_id(self, value):
        if not isinstance(value, int) or value <= 0:
            raise ValueError("Discipline ID must be a positive integer.")
        self.__discipline_id = value

    def get_student_id(self):
        return self.__student_id

    def set_student_id(self, value):
        if not isinstance(value, int) or value <= 0:
            raise ValueError("Student ID must be a positive integer.")
        self.__student_id = value

    def get_grade_value(self):
        return self.__grade_value

    def set_grade_value(self, value):
        if not isinstance(value, (int, float)) or not (1.0 <= value <= 10.0):
            raise ValueError("Grade value must be a float between 1.0 and 10.0.")
        self.__grade_value = value

    def __repr__(self):
        return f"Grade(DisciplineID={self.__discipline_id}, StudentID={self.__student_id}, Value={self.__grade_value})"

    def __eq__(self, other):
        if isinstance(other, Grade):
            return (
                self.__discipline_id == other.__discipline_id and
                self.__student_id == other.__student_id and
                self.__grade_value == other.__grade_value
            )
        return False