from domain.driver import Driver
from driver_repo.driver_base_repo import DriverRepository

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
                    name = parts[0]
                    x = int(parts[1])
                    y = int(parts[2])
                    driver = Driver(name, x, y)
                    self._entities[name] = driver
        except FileNotFoundError:
            self._entities = {}

    def __write_all_to_file(self):
        with open(self.__file_path, "w") as f:
            for driver in self._entities.values():
                f.write(f"{driver.get_name()},{driver.get_position_x()},{driver.get_position_y()}\n")


    def generate_drivers(self):
        """
        Generate a predefined set of drivers and populate the repository.
        The format for each driver is: Name, x-coordinate, y-coordinate.
        """
        # Creating predefined driver objects with name, x, and y
        d1 = Driver("John Doe", 10, 20)
        d2 = Driver("Jane Smith", 15, 25)
        d3 = Driver("Michael Johnson", 30, 30)
        d4 = Driver("Emily Davis", 40, 45)
        d5 = Driver("Robert Brown", 50, 50)
        d6 = Driver("Sophia Wilson", 60, 65)
        d7 = Driver("William Garcia", 70, 75)
        d8 = Driver("Olivia Martinez", 80, 85)
        d9 = Driver("James Rodriguez", 90, 95)
        d10 = Driver("Isabella Hernandez", 100, 105)

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
        super().add_entity(entity)
        self.__write_all_to_file()

    def update_entity(self, entity):
        self.__read_all_from_file()
        super().update_entity(entity)
        self.__write_all_to_file()

    def delete_by_name(self, name):
        self.__read_all_from_file()
        super().delete_by_name(name)
        self.__write_all_to_file()

    def get_all(self):
        self.__read_all_from_file()
        return super().get_all()
