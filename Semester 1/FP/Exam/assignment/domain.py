class Assignment:

    def __init__(self, id, student_name, solution):
        self._id = id
        self._student_name = student_name
        self._solution = solution

    def get_id(self):
        return self._id

    def get_student_name(self):
        return self._student_name

    def get_solution(self):
        return self._solution

    def set_id(self, new_id):
        self._id = new_id

    def set_student_name(self, new_student_name):
        self._student_name = new_student_name

    def set_solution(self, new_solution):
        self._solution = new_solution

    def __str__(self):
        return f"{self._id} {self._student_name} {self._solution}"