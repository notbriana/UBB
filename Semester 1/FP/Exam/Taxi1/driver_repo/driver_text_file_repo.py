from driver_repo.driver_base_repo import DriverRepository
from domain.driver_domain import Driver


class DriverTextFileRepository(DriverRepository):
    def __init__(self, file_path):
        super().__init__()
        self.__file_path = file_path
        self.generate_drivers()

    def __read_all_from_file(self):
        try:
            with open(self.__file_path, "r") as f:
                self._entities.clear()
                for line in f:
                    parts = line.strip().split(",")
                    id_driver = int(parts[0])
                    name = parts[1]
                    driver = Driver(id_driver, name)
                    self._entities[id_driver] = driver
        except FileNotFoundError:
            self._entities = {}

    def __write_all_to_file(self):
        with open(self.__file_path, "w") as f:
            for driver in self._entities.values():
                f.write(f"{driver.get_id_driver()},{driver.get_name()}\n")

    def generate_drivers(self):
        """
        Generate a predefined set of drivers and populate the repository.
        """
        d1 = Driver(1, "John Doe")
        d2 = Driver(2, "Jane Smith")
        d3 = Driver(3, "Michael Johnson")
        d4 = Driver(4, "Emily Davis")
        d5 = Driver(5, "Robert Brown")
        d6 = Driver(6, "Sophia Wilson")
        d7 = Driver(7, "William Garcia")
        d8 = Driver(8, "Olivia Martinez")
        d9 = Driver(9, "James Rodriguez")
        d10 = Driver(10, "Isabella Hernandez")

        if len(self._entities) == 0:  # Ensures drivers are only added if repository is empty
            self._entities[1] = d1
            self._entities[2] = d2
            self._entities[3] = d3
            self._entities[4] = d4
            self._entities[5] = d5
            self._entities[6] = d6
            self._entities[7] = d7
            self._entities[8] = d8
            self._entities[9] = d9
            self._entities[10] = d10

        self.__write_all_to_file()

    def add_entity(self, entity):
        self.__read_all_from_file()
        super().add_driver(entity)
        self.__write_all_to_file()

    def update_entity(self, entity):
        self.__read_all_from_file()
        super().update_driver(entity)
        self.__write_all_to_file()

    def delete_by_id(self, id_driver):
        self.__read_all_from_file()
        super().delete_by_id(id_driver)
        self.__write_all_to_file()

    def get_all(self):
        self.__read_all_from_file()
        return super().get_all()
