from domain import Assignment


class TextFileRepo:
    def __init__(self, file_name):
        self._file_name = file_name
        self._data = []
        self.generate_assignment()

    def __load(self):
        try:
            with open(self._file_name, "r") as f:
                lines = f.readlines()
                for line in lines:
                    line = line.strip()
                    if line != "":
                        parts = line.split(",")
                        id = int(parts[0])
                        student_name = parts[1]
                        solution = parts[2]
                        assignment = Assignment(id, student_name, solution)
                        self._data.append(assignment)
        except FileNotFoundError:
            print("File not found")

    def __save(self):
        with open(self._file_name, "w") as f:
            for assignment in self._data:
                f.write(f"{assignment.get_id()},{assignment.get_student_name()},{assignment.get_solution()}\n")

    def generate_assignment(self):
        "solution is a string"
        a1 = Assignment(1, "Theodor Mihail", "I will make sure to implement a layered architecture solution")
        a2 = Assignment(2, "Ana Blandiana", "The program is layered")
        a3 = Assignment(3, "Corina Escu", "I did not understand layered architecture")
        a4 = Assignment(4, "Lara Jula", "My proposed solution does not include layers")
        a5 = Assignment(5, "Doru Flaore", "I will implement a layered architecture")
        a6 = Assignment(6, "Denisa Emrich", "I will implement a layered architecture")
        a7 = Assignment(7, "Adela Haban", "I did not implement a layered architecture")
        a8 = Assignment(8, "Mihai Emil", "My solution is layered")
        a9 = Assignment(9, "Mihai Eminescu", "I don't understand layered architecture")
        a10 = Assignment(10, "Titulescu Noe", "I will try to implement a layered architecture")

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

    def add(self, assignment):
        self._data.append(assignment)
        self.__save()

    def get_all(self):
        return self._data

    def update(self, assignment):
        for i in range(len(self._data)):
            if self._data[i].get_id() == assignment.get_id():
                self._data[i] = assignment
                self.__save()
                return
        raise ValueError(f"Assignment with ID {assignment.get_id()} not found.")

    def delete(self, assignment_id):
        for i in range(len(self._data)):
            if self._data[i].get_id() == assignment_id:
                del self._data[i]
                self.__save()
                return
        raise ValueError(f"Assignment with ID {assignment_id} not found.")

    def find_by_id(self, assignment_id):
        assignment = [assignment for assignment in self._data if assignment.get_id() == assignment_id]
        if len(assignment) > 0:
            return assignment[0]
        else:
            return None

    def get_all_ids(self):
        return [assignment.get_id() for assignment in self._data]
