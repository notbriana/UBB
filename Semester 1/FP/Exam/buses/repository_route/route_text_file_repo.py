from domain.route import Route
from repository_route.route_base_repo import RouteBaseRepo

class RouteTextFile(RouteBaseRepo):

    def __init__(self, file_name):
        super().__init__()
        self._file_name = file_name
        self.generate_routes()

    def __load(self):
        try:
            with open(self._file_name, "r") as file:
                return file.read()
        except FileNotFoundError:
            return ""

    def __save(self):
        with open(self._file_name, "w") as file:
            for route in self._entities.values():
                file.write(f"{route.get_route_code()},{route.get_length()}\n")

    def generate_routes(self):
        """
        Generate 10 routes and populate the repository.
        """
        r1 = Route(1, 10)
        r2 = Route(2, 20)
        r3 = Route(3, 30)
        r4 = Route(4, 40)
        r5 = Route(5, 50)
        r6 = Route(6, 60)
        r7 = Route(7, 70)
        r8 = Route(8, 80)
        r9 = Route(9, 90)
        r10 = Route(10, 100)

        if len(self._entities) == 0:
            self._entities[1] = r1
            self._entities[2] = r2
            self._entities[3] = r3
            self._entities[4] = r4
            self._entities[5] = r5
            self._entities[6] = r6
            self._entities[7] = r7
            self._entities[8] = r8
            self._entities[9] = r9
            self._entities[10] = r10

        self.__save()

    def add_entity(self, entity):
        self.__load()
        super().add_route(entity)
        self.__save()

    def update_entity(self, entity):
        self.__load()
        super().update_route(entity)
        self.__save()

    def delete_entity(self, entity):
        self.__load()
        super().delete_by_id(entity.get_route_code())
        self.__save()

    def get_all(self):
        self.__load()
        return super().get_all()

    def search_by_id(self, route_code):
        self.__load()
        return super().search_by_id(route_code)



