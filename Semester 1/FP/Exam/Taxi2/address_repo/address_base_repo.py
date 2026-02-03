class AddressRepository:

    def __init__(self):
        self._entities = {}

    def add_entity(self, entity):
        if entity.get_address_id() in self._entities:
            raise ValueError("Entity already exists")
        self._entities[entity.get_address_id()] = entity

    def update_entity(self, entity):
        if entity.get_address_id() not in self._entities:
            raise ValueError("Entity doesn't exist")
        self._entities[entity.get_address_id()] = entity

    def delete_by_id(self, address_id):
        if address_id not in self._entities:
            raise ValueError("Entity not found.")
        del self._entities[address_id]

    def find_by_id(self, address_id):
        return self._entities[address_id]

    def get_all(self):
        return list(self._entities.values())

