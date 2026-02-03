class UI:
    def __init__(self, service):
        self._service = service

    def _print_menu(self):
        print("Commands:")
        print("add - Add assignment")
        print("list - List assignments")
        print("check - Check for dishonesty")
        print("exit - Exit")

    def _add_assignment(self):
        try:
            id = int(input("Enter assignment ID: "))
            student_name = input("Enter student name: ")
            solution = input("Enter solution: ")
            self._service.add_assignment(id, student_name, solution)
            print("Assignment added successfully.")
        except ValueError as e:
            print(f"Error: {e}")

    def _list_assignments(self):
        assignments = self._service.get_all_assignments_increasing_order()
        for assignment in assignments:
            print(assignment)

    def _check_dishonesty(self):
        pairs = self._service.dishonesty_check()
        if not pairs:
            print("No dishonest assignments found.")
        else:
            for a1, a2, percentage in pairs:
                print(f"Assignments {a1.get_id()} and {a2.get_id()} have {percentage:.2f}% common words.")

    def run(self):
        while True:
            self._print_menu()
            command = input("Enter command: ").strip().lower()
            if command == "add":
                self._add_assignment()
            elif command == "list":
                self._list_assignments()
            elif command == "check":
                self._check_dishonesty()
            elif command == "exit":
                print("Exiting...")
                break
            else:
                print("Invalid command. Please try again.")