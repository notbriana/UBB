class GradeRepository:
    def __init__(self):
        self._entities = {}

    def add_entity(self, entity):
        if entity.get_discipline_id() in self._entities:
            raise ValueError("Entity already exists!")
        self._entities[(entity.get_discipline_id(), entity.get_student_id())] = entity

    def update_entity(self, entity):
        key = (entity.get_discipline_id(), entity.get_student_id())
        if key not in self._entities:
            raise Exception("Entity does not exist.")
        self._entities[key] = entity

    def search_by_id(self, discipline_id, student_id):
        key = (discipline_id, student_id)
        if key not in self._entities:
            raise ValueError("Entity doesn't exist!")
        return self._entities[key]

    def delete_by_id(self, discipline_id, student_id):
        key = (discipline_id, student_id)
        if key not in self._entities:
            raise ValueError("Entity not found.")
        del self._entities[key]

    def get_all(self):
        return list(self._entities.values())
