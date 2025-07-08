class DisciplineRepository:
    def __init__(self):
        self._entities = {}

    def add_entity(self, entity):
        if entity.get_discipline_id() in self._entities:
            raise ValueError("Entity already exists!")
        self._entities[entity.get_discipline_id()] = entity

    def update_entity(self, entity):
        if entity.get_discipline_id() not in self._entities:
            raise Exception("Entity does not exist.")
        self._entities[entity.get_discipline_id()] = entity

    def search_by_id(self, id_discipline):
        if id_discipline not in self._entities or self._entities[id_discipline].is_deleted():
            raise ValueError("Entity doesn't exist!")
        return self._entities[id_discipline]

    def delete_by_id(self, id_discipline):
        if id_discipline not in self._entities:
            raise ValueError("Entity not found.")
        self._entities[id_discipline].delete()

    def get_all(self):
        return [entity for entity in self._entities.values() if not entity.is_deleted()]
