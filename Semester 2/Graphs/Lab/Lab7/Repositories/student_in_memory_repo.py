from Repositories.student_base_repo import Repository

class StudentMemoryRepository(Repository):
    def __init__(self):
        super().__init__()
        self._entities = {}

    def add_entity(self, entity):
        self._entities[entity.get_id_entity()] = entity

    def update_entity(self, entity):
        if entity.get_id_entity() not in self._entities:
            raise Exception("Entity does not exist.")
        self._entities[entity.get_id_entity()] = entity

    def delete_by_id(self, id_entity):
        if id_entity not in self._entities:
            raise Exception("Entity does not exist.")
        del self._entities[id_entity]

    def get_all(self):
        return [entity for entity in self._entities.values() if not entity.is_deleted()]
