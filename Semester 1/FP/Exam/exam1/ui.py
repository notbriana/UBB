class UI:
    def __init__(self, service):
        self._service = service

    def print_menu(self):
        print("\nMenu:")
        print("1. Add a new student")
        print("2. Display all students")
        print("3. Give bonus to students")
        print("4. Find students by name")
        print("5. Exit")

    def add_student(self):
        try:
            id = int(input("Enter student ID: "))
            name = input("Enter student name: ").strip()
            attendance_count = int(input("Enter attendance count: "))
            grade = float(input("Enter grade: "))
            self._service.add(id, name, attendance_count, grade)
            print("Student added successfully.")
        except ValueError as e:
            print(f"Error: {e}")

    def display_all_students(self):
        students = self._service.get_all()
        if not students:
            print("No students found.")
        else:
            print("\nStudents (sorted by grade, then name):")
            for student in students:
                print(f"ID: {student.get_id()}, Name: {student.get_name()}, Attendance: {student.get_attendance_count()}, Grade: {student.get_grade()}")

    def give_bonus(self):
        try:
            p = int(input("Enter minimum attendance count: "))
            b = int(input("Enter bonus grade: "))
            self._service.give_bonus(p, b)
            print("Bonus applied successfully.")
        except ValueError as e:
            print(f"Error: {e}")

    def find_students_by_name(self):
        substring = input("Enter part of the name to search: ").strip()
        students = self._service.find_by_name(substring)
        if not students:
            print("No students found with the given name.")
        else:
            print("\nMatching students (sorted by name):")
            for student in students:
                print(f"ID: {student.get_id()}, Name: {student.get_name()}, Attendance: {student.get_attendance_count()}, Grade: {student.get_grade()}")

    def run(self):
        while True:
            self.print_menu()
            choice = input("Choose an option: ").strip()
            if choice == "1":
                self.add_student()
            elif choice == "2":
                self.display_all_students()
            elif choice == "3":
                self.give_bonus()
            elif choice == "4":
                self.find_students_by_name()
            elif choice == "5":
                print("Exiting program.")
                break
            else:
                print("Invalid choice. Please try again.")
