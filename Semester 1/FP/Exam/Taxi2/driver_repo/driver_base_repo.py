class DriverRepository:

    def __init__(self):
        self._entities = {}

    def add_entity(self, entity):
        if entity.get_name() in self._entities:
            raise ValueError("Entity already exists")
        self._entities[entity.get_name()] = entity

    def update_entity(self, entity):
        if entity.get_name() not in self._entities:
            raise ValueError("Entity doesn't exist")
        self._entities[entity.get_name()] = entity

    def delete_by_name(self, name):
        if name not in self._entities:
            raise ValueError("Entity not found.")
        del self._entities[name]

    def find_by_id(self, name):
        return self._entities[name]

    def get_all(self):
        return list(self._entities.values())

