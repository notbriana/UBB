import copy

class Repository:

    def __init__(self):
        self._entities = {}

    def add_entity(self, entity):
        if entity.get_id_entity() in self._entities:
            raise ValueError("Entity already exists!")
        self._entities[entity.get_id_entity()] = entity

    def update_entity(self, entity):
        if entity.get_id_entity() not in self._entities:
            raise Exception("Entity does not exist.")
        self._entities[entity.get_id_entity()] = entity

    def search_by_id(self, id_entity):
        if id_entity not in self._entities or self._entities[id_entity].is_deleted():
            raise ValueError("Entity doesn't exist!")
        return self._entities[id_entity]

    def delete_by_id(self, id_entity):
        if id_entity not in self._entities:
            raise ValueError("Entity not found.")
        self._entities[id_entity].delete()

    def get_all(self):
        return [entity for entity in self._entities.values() if not entity.is_deleted()]
    
    def __deepcopy__(self, memo):
        new_repo = Repository()
        new_repo._entities = copy.deepcopy(self._entities, memo)
        return new_repo

