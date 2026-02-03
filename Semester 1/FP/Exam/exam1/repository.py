from domain import Student

class TextFileRepo:
    def __init__(self, file_name):
        self._data = []
        self.__file_name = file_name
        self.__load()
        self.generate_students()

    def __load(self):
        try:
            with open(self.__file_name, "r") as f:
                self._data.clear()
                for line in f:
                    line = line.strip()
                    if line:  # Skip empty lines
                        parts = line.split(",")
                        id = int(parts[0])
                        name = parts[1]
                        attendance_count = int(parts[2])
                        grade = int(parts[3])
                        student = Student(id, name, attendance_count, grade)
                        self._data.append(student)
        except FileNotFoundError:
            # If the file doesn't exist, start with an empty repository
            self._data = []

    def __save(self):
        with open(self.__file_name, "w") as f:
            for student in self._data:
                f.write(
                    f"{student.get_id()},{student.get_name()},{student.get_attendance_count()},{student.get_grade()}\n")

    def generate_students(self):
        a1 = Student(1, "Theodor Mihail", 10, 9)
        a2 = Student(2, "Ana Blandiana", 15, 5)
        a3 = Student(3, "Corina Escu", 1, 10)
        a4 = Student(4, "Lara Jula", 20, 6)
        a5 = Student(5, "Doru Flaore", 22, 6)
        a6 = Student(6, "Denisa Emrich", 2, 10)
        a7 = Student(7, "Adela Haban", 50, 7)
        a8 = Student(8, "Mihai Emil", 2, 5)
        a9 = Student(9, "Mihai Eminescu", 3, 7)
        a10 = Student(10, "Titulescu Noe", 10, 3)

        if len(self._data) == 0:
            self._data.append(a1)
            self._data.append(a2)
            self._data.append(a3)
            self._data.append(a4)
            self._data.append(a5)
            self._data.append(a6)
            self._data.append(a7)
            self._data.append(a8)
            self._data.append(a9)
            self._data.append(a10)

        self.__save()

    def add(self, student):
        if student.get_id() < 0 or self.find(student.get_id()) is not None:
            raise ValueError("The id must be unique and a positive integer")
        elif len(student.get_name()) < 7:
            raise ValueError("The name must be at least 7 characters long")
        else:
            self._data.append(student)
        self.__save()

    def update(self, student):
        """
        Updates an existing student in the collection.

        :param student: The student object with updated information.
        :raises ValueError: If the student's name is too short or the student does not exist in the collection.
        """
        # Validate name length
        if len(student.get_name()) < 7:
            raise ValueError("The name must be at least 7 characters long.")

        # Find the existing student by ID
        for i, existing_student in enumerate(self._data):
            if existing_student.get_id() == student.get_id():
                # Replace the existing student with the updated one
                self._data[i] = student
                self.__save()  # Persist changes
                return

        # Raise error if student not found
        raise ValueError("Student with the given ID does not exist.")

    def find(self, student_id):
        students = [a for a in self._data if a.get_id() == student_id]
        if len(students) != 0:
            return students[0]
        else:
            return None

    def get_all(self):
        return self._data