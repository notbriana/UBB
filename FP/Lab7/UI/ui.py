from Services.student_service import StudentService

class UI:
    def __init__(self, service):
        self.__service = service

    def display_menu(self):
        while True:
            print("\n----- Students Management -----")
            print("1. Add Student")
            print("2. Display Students")
            print("3. Filter by Group")
            print("4. Undo Last Operation")
            print("6. Exit")
            choice = input("Choose an option: ")

            if choice == "1":
                self.add_student()
            elif choice == "2":
                self.display_students()
            elif choice == "3":
                self.filter_students_by_group()
            elif choice == "4":
                self.undo_last_operation()
            elif choice == "6":
                break
            else:
                print("Invalid choice, try again.")

    def add_student(self):
        id_student = int(input("Enter ID: "))
        name = input("Enter Name: ")
        group = int(input("Enter Group: "))
        self.__service.add_student(id_student, name, group)
        print("Student added.")

    def display_students(self):
        students = self.__service.show_all()
        if not students:
            print("No students to display.")
        for student in students:
            print(student)

    def filter_students_by_group(self):
        group = int(input("Enter group: "))
        self.__service.filter_students_by_group(group)
        
    def undo_last_operation(self):
        self.__service.undo()
