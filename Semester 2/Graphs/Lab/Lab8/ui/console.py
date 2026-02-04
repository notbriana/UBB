class Console:
    def __init__(self, student_service, discipline_service, grade_service, undo_service):
        self._student_service = student_service
        self._discipline_service = discipline_service
        self._grade_service = grade_service
        self._undo_service = undo_service

    def run(self):
        while True:
            print("\nMenu:")
            print("1. Manage Students")
            print("2. Manage Disciplines")
            print("3. Manage Grades")
            print("0. Exit")
            option = input("Choose an option: ").strip()

            if option == "1":
                self._manage_students()
            elif option == "2":
                self._manage_disciplines()
            elif option == "3":
                self._manage_grades()
            elif option == "4":
                self._manage_undo()
            elif option == "5":
                self._manage_redo()
            elif option == "0":
                print("Exiting program.")
                break
            else:
                print("Invalid option. Please try again.")

    def _manage_undo(self):
        self._undo_service.undo()
        
    def _manage_redo(self):
        self._undo_service.redo()  
    
    def _manage_students(self):
        while True:
            print("\nStudent Management:")
            print("1. Add Student")
            print("2. Remove Student")
            print("3. Update Student")
            print("4. List Students")
            print("5. Search Students")
            print("0. Back to Main Menu")
            option = input("Choose an option: ").strip()

            if option == "1":
                student_id = int(input("Enter Student ID: "))
                name = input("Enter Student Name: ")
                try:
                    self._student_service.add_student(student_id, name)
                    print("Student added successfully.")
                except ValueError as e:
                    print(e)
            elif option == "2":
                student_id = int(input("Enter Student ID to remove: "))
                try:
                    self._student_service.remove_student(student_id)
                    print("Student removed successfully.")
                except ValueError as e:
                    print(e)
            elif option == "3":
                student_id = int(input("Enter Student ID to update: "))
                name = input("Enter new Student Name: ")
                try:
                    self._student_service.update_student(student_id, name)
                    print("Student updated successfully.")
                except ValueError as e:
                    print(e)
            elif option == "4":
                students = self._student_service.list_students()
                print("Students:")
                for student in students:
                    print(student)
            elif option == "5":
                search_term = input("Enter search term (ID or Name): ")
                students = self._student_service.search_students(search_term)
                print("Search Results:")
                for student in students:
                    print(student)
            elif option == "0":
                break
            else:
                print("Invalid option. Please try again.")

    def _manage_disciplines(self):
        while True:
            print("\nDiscipline Management:")
            print("1. Add Discipline")
            print("2. Remove Discipline")
            print("3. Update Discipline")
            print("4. List Disciplines")
            print("5. Search Disciplines")
            print("0. Back to Main Menu")
            option = input("Choose an option: ").strip()

            if option == "1":
                discipline_id = int(input("Enter Discipline ID: "))
                name = input("Enter Discipline Name: ")
                try:
                    self._discipline_service.add_discipline(discipline_id, name)
                    print("Discipline added successfully.")
                except ValueError as e:
                    print(e)
            elif option == "2":
                discipline_id = int(input("Enter Discipline ID to remove: "))
                try:
                    self._discipline_service.remove_discipline(discipline_id)
                    print("Discipline removed successfully.")
                except ValueError as e:
                    print(e)
            elif option == "3":
                discipline_id = int(input("Enter Discipline ID to update: "))
                name = input("Enter new Discipline Name: ")
                try:
                    self._discipline_service.update_discipline(discipline_id, name)
                    print("Discipline updated successfully.")
                except ValueError as e:
                    print(e)
            elif option == "4":
                disciplines = self._discipline_service.list_disciplines()
                print("Disciplines:")
                for discipline in disciplines:
                    print(discipline)
            elif option == "5":
                search_term = input("Enter search term (ID or Name): ")
                disciplines = self._discipline_service.search_disciplines(search_term)
                print("Search Results:")
                for discipline in disciplines:
                    print(discipline)
            elif option == "0":
                break
            else:
                print("Invalid option. Please try again.")

    def _manage_grades(self):
        while True:
            print("\nGrade Management:")
            print("1. Add Grade")
            print("2. List Grades")
            print("3. Remove Grades by Student")
            print("4. Remove Grades by Discipline")
            print("0. Back to Main Menu")
            option = input("Choose an option: ").strip()

            if option == "1":
                discipline_id = int(input("Enter Discipline ID: "))
                student_id = int(input("Enter Student ID: "))
                grade_value = float(input("Enter Grade Value (1.0 to 10.0): "))
                try:
                    self._grade_service.add_grade(discipline_id, student_id, grade_value)
                    print("Grade added successfully.")
                except ValueError as e:
                    print(e)
            elif option == "2":
                grades = self._grade_service.list_grades()
                print("Grades:")
                for grade in grades:
                    print(grade)
            elif option == "3":
                student_id = int(input("Enter Student ID to remove grades for: "))
                try:
                    self._grade_service.remove_grades_by_student(student_id)
                    print("Grades removed successfully.")
                except ValueError as e:
                    print(e)
            elif option == "4":
                discipline_id = int(input("Enter Discipline ID to remove grades for: "))
                try:
                    self._grade_service.remove_grades_by_discipline(discipline_id)
                    print("Grades removed successfully.")
                except ValueError as e:
                    print(e)
            elif option == "0":
                break
            else:
                print("Invalid option. Please try again.")
