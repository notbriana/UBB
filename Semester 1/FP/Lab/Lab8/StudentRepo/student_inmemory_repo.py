from StudentRepo.student_base_repo import StudentRepository


class StudentMemoryRepository(StudentRepository):
    def __init__(self):
        super().__init__()

    def add_entity(self, entity):
        super().add_entity(entity)

    def update_entity(self, entity):
        super().update_entity(entity)

    def delete_by_id(self, student_id):
        super().delete_by_id(student_id)

    def get_all(self):
        return super().get_all()
