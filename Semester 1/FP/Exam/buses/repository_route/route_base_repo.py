class RouteBaseRepo:
    def __init__(self):
        self._entities = {}

    def add_route(self, entity):
        if entity.get_route_code() in self._entities:
            raise ValueError("Entity already exists!")
        self._entities[entity.get_route_code()] = entity

    def update_route(self, entity):
        if entity.get_route_code() not in self._entities:
            raise ValueError("Entity does not exist!")
        self._entities[entity.get_route_code()] = entity

    def search_by_id(self, route_code):
        if route_code not in self._entities:
            raise ValueError("Entity doesn't exist")
        return self._entities[route_code]

    def delete_by_id(self, route_code):
        if route_code not in self._entities:
            raise ValueError("Entity does not exist!")
        del self._entities[route_code]

    def get_all(self):
        return list(self._entities.values())



