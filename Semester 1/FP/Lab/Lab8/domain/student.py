class Student:
    def __init__(self, student_id: int, name: str):
        self.__student_id = student_id
        self.__name = name

    def get_student_id(self):
        return self.__student_id

    def set_student_id(self, value):
        if not isinstance(value, int) or value <= 0:
            raise ValueError("Student ID must be a positive integer.")
        self.__student_id = value

    def get_name(self):
        return self.__name

    def set_name(self, value):
        if not isinstance(value, str) or not value.strip():
            raise ValueError("Name must be a non-empty string.")
        self.__name = value

    def __repr__(self):
        return f"Student(ID={self.__student_id}, Name={self.__name})"

    def __eq__(self, other):
        if isinstance(other, Student):
            return self.__student_id == other.__student_id and self.__name == other.__name
        return False
