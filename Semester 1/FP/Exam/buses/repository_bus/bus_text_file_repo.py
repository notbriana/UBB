from domain.bus import Bus
from repository_bus.bus_base_repo import BusBaseRepo

class BusTextFile(BusBaseRepo):
    def __init__(self, file_path):
        super().__init__()
        self.__file_path = file_path
        self.generate_buses()

    def __load(self):
        try:
            with open(self.__file_path, "r") as f:
                self._entities.clear()
                for line in f:
                    parts = line.strip().split(",")
                    bus_id = int(parts[0])
                    route_code = int(parts[1])
                    model = parts[2]
                    times_used_on_route = int(parts[3])
                    bus = Bus(bus_id, route_code, model, times_used_on_route)
                    self._entities[bus_id] = bus
        except FileNotFoundError:
            self._entities = {}

    def __save(self):
        with open(self.__file_path, "w") as f:
            for bus in self._entities.values():
                f.write(f"{bus.get_id()},{bus.get_route_code()},{bus.get_model()},{bus.get_times_used_on_route()}\n")

    def generate_buses(self):
        """
        Generate 10 buses and populate the repository.
        """
        b1 = Bus(1, 1, "Mercedes", 5)
        b2 = Bus(2, 2, "Volvo", 10)
        b3 = Bus(3, 3, "Scania", 15)
        b4 = Bus(4, 4, "Iveco", 20)
        b5 = Bus(5, 5, "MAN", 25)
        b6 = Bus(6, 5, "Renault", 30)
        b7 = Bus(7, 5, "DAF", 35)
        b8 = Bus(8, 8, "Setra", 40)
        b9 = Bus(9, 9, "Neoplan", 45)
        b10 = Bus(10, 10, "Van Hool", 50)

        if len(self._entities) == 0:
            self._entities[1] = b1
            self._entities[2] = b2
            self._entities[3] = b3
            self._entities[4] = b4
            self._entities[5] = b5
            self._entities[6] = b6
            self._entities[7] = b7
            self._entities[8] = b8
            self._entities[9] = b9
            self._entities[10] = b10

        self.__save()

    def add_entity(self, entity):
        self.__load()
        super().add_bus(entity)
        self.__save()

    def update_entity(self, entity):
        self.__load()
        super().update_bus(entity)
        self.__save()

    def delete_by_id(self, bus_id):
        self.__load()
        super().delete_by_id(bus_id)
        self.__save()

    def get_all(self):
        self.__load()
        return super().get_all()

    def search_by_id(self, bus_id):
        self.__load()
        return super().search_by_id(bus_id)



