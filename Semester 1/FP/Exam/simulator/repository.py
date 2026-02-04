from domain import Taxi


class TextFileRepo:

    def __init__(self, file_name):
        self._entities = []
        self._file_name = file_name
        self.__load()

    def __load(self):
        try:
            with open(self._file_name, "r") as f:
                self._entities.clear()
                for line in f:
                    line = line.strip()
                    if line:  # Skip empty lines
                        parts = line.split(",")
                        id = int(parts[0])
                        x = int(parts[1])
                        y = int(parts[2])
                        total_fares = int(parts[3])
                        entity = Taxi(id, x, y, total_fares)
                        self._entities.append(entity)
        except FileNotFoundError:
            # If the file doesn't exist, start with an empty repository
            self._entities = []

    def __save(self):
        with open(self._file_name, "w") as f:
            for entity in self._entities:
                f.write(f"{entity.get_id()},{entity.get_x()},{entity.get_y()},{entity.get_total_fares()}\n")



    def add(self, entity):
        self._entities.append(entity)
        self.__save()

    def get_all(self):
        return self._entities

    def update(self, entity):
        for i in range(len(self._entities)):
            if self._entities[i].get_id() == entity.get_id():
                self._entities[i] = entity
                self.__save()
                return
        raise ValueError("Entity not found.")

    def delete(self, entity_id):
        for i in range(len(self._entities)):
            if self._entities[i].get_id() == entity_id:
                del self._entities[i]
                self.__save()
                return
        raise ValueError("Entity not found.")

    def find_by_id(self, entity_id):
        for entity in self._entities:
            if entity.get_id() == entity_id:
                return entity
        return None
