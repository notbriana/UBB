class DriverRepository:

    def __init__(self):
        self._entities = {}

    def add_driver(self, entity):
        if entity.get_id_driver() in self._entities:
            raise ValueError("Entity already exists!")
        self._entities[entity.get_id_driver()] = entity

    def update_driver(self, entity):
        if entity.get_id_driver() not in self._entities:
            raise ValueError("Entity does not exist!")
        self._entities[entity.get_id_driver()] = entity

    def search_by_id(self, id_driver):
        if id_driver not in self._entities:
            raise ValueError("Entity doesn't exist")
        return self._entities[id_driver]

    def delete_by_id(self, id_driver):
        if id_driver not in self._entities:
            raise ValueError("Driver does not exist!")
        self._entities[id_driver].mark_as_deleted()
        del self._entities[id_driver]

    def get_all(self):
        return list(self._entities.values())
