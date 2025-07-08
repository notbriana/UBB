from domain.student import Student
from services.undo_services import FunctionCall, Operation, CascadedOperation

class StudentService:
    def __init__(self, student_repo, grade_repo, undo_services):
        self._student_repo = student_repo
        self._grade_repo = grade_repo
        self._undo_services = undo_services

    def add_student(self, student_id, name):
        """Add a new student to the repository."""
        student = Student(student_id, name)
        function_undo = FunctionCall(self._student_repo.delete_by_id, student_id)
        function_redo = FunctionCall(self._student_repo.add_entity, student)
        operation = Operation(function_undo, function_redo)
        self._undo_services.record_undo(operation)
        self._student_repo.add_entity(student)

    def remove_student(self, student_id):
        """Remove a student from the repository by ID."""
        student = self._student_repo.find_by_id(student_id)
        if not student:
            raise ValueError("Student not found.")
        
        function_redo = FunctionCall(self._student_repo.delete_by_id, student_id)
        function_undo = FunctionCall(self._student_repo.add_entity, student)
        operations = [Operation(function_undo, function_redo)]
        self._student_repo.delete_by_id(student_id)
        
        for grade in self._grade_repo.get_all():
            if grade.get_student_id() == student_id:
                function_redo = FunctionCall(self._grade_repo.delete_by_id, grade.get_student_id())
                function_undo = FunctionCall(self._grade_repo.add_entity, grade)
                operations.append(Operation(function_undo, function_redo))
                self._grade_repo.delete_by_id(grade.get_student_id())
                
        cascaded_operation = CascadedOperation(*operations)
        self._undo_services.record_undo(cascaded_operation)

    def update_student(self, student_id, new_name):
        """Update the name of a student."""
        student = self._student_repo.find_by_id(student_id)
        if not student:
            raise ValueError("Student not found.")
        updated_student = Student(student_id, new_name)
        self._student_repo.update(student_id, updated_student)

    def list_students(self):
        """List all students in the repository."""
        return self._student_repo.get_all()

    def search_students(self, search_term):
        """Search for students by name or ID."""
        return [
            student
            for student in self._student_repo.get_all()
            if search_term.lower() in student.get_name().lower() or str(student.get_student_id()) == search_term
        ]

    def find_by_id(self, student_id):
        """Find and return a student by its ID."""
        return self._student_repo.find_by_id(student_id)
