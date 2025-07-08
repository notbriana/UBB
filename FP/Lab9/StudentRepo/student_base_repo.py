class StudentRepository:
    def __init__(self):
        self._entities = {}

    def add_entity(self, entity):
        if entity.get_student_id() in self._entities:
            raise ValueError("Entity already exists!")
        self._entities[entity.get_student_id()] = entity

    def update_entity(self, entity):
        student_id = entity.get_student_id()
        if student_id not in self._entities:
            raise Exception("Entity does not exist.")
        self._entities[student_id] = entity

    def delete_by_id(self, student_id):
        if student_id not in self._entities:
            raise ValueError("Entity not found.")
        del self._entities[student_id]

    def get_all(self):
        return list(self._entities.values())
