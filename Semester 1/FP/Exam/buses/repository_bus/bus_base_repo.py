class BusBaseRepo:
    def __init__(self):
        self._entities = {}

    def add_bus(self, entity):
        if entity.get_id() in self._entities:
            raise ValueError("Entity already exists!")
        self._entities[entity.get_id()] = entity

    def update_bus(self, entity):
        if entity.get_id() not in self._entities:
            raise ValueError("Entity does not exist!")
        self._entities[entity.get_id()] = entity

    def search_by_id(self, bus_id):
        if bus_id not in self._entities:
            raise ValueError("Entity doesn't exist")
        return self._entities[bus_id]

    def delete_by_id(self, bus_id):
        if bus_id not in self._entities:
            raise ValueError("Entity does not exist!")
        del self._entities[bus_id]

    def get_all(self):
        return list(self._entities.values())

