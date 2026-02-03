from address_repo.address_base_repo import AddressRepository
from domain.address import Address


class AddressTextFileRepository(AddressRepository):
    def __init__(self, file_path):
        super().__init__()
        self.__file_path = file_path
        self.generate_addresses()

    def __read_all_from_file(self):
        try:
            with open(self.__file_path, "r") as f:
                self._entities.clear()
                for line in f:
                    parts = line.strip().split(",")
                    address_id = int(parts[0])
                    name = parts[1]
                    x = float(parts[2])
                    y = float(parts[3])
                    address = Address(address_id, name, x, y)
                    self._entities[address_id] = address
        except FileNotFoundError:
            self._entities = {}

    def __write_all_to_file(self):
        with open(self.__file_path, "w") as f:
            for address in self._entities.values():
                f.write(
                    f"{address.get_address_id()},{address.get_address_name()},{address.get_address_x()},{address.get_address_y()}\n")

    def generate_addresses(self):
        """
        Generate a predefined set of addresses and populate the repository.
        """
        # Creating predefined address objects (ensure the Address class is properly defined)
        a1 = Address(1, "123 Main St", 10, 20)
        a2 = Address(2, "456 Elm St", 15, 25)
        a3 = Address(3, "789 Oak St", 30, 30)
        a4 = Address(4, "101 Pine St", 40, 45)
        a5 = Address(5, "202 Maple St", 50, 50)
        a6 = Address(6, "303 Birch St", 60, 65)
        a7 = Address(7, "404 Cedar St", 70, 75)
        a8 = Address(8, "505 Willow St", 80, 85)
        a9 = Address(9, "606 Cherry St", 90, 95)
        a10 = Address(10, "707 Chestnut St", 89, 90)

        if len(self._entities) == 0:  # Ensures addresses are only added if repository is empty
            self._entities[1] = a1
            self._entities[2] = a2
            self._entities[3] = a3
            self._entities[4] = a4
            self._entities[5] = a5
            self._entities[6] = a6
            self._entities[7] = a7
            self._entities[8] = a8
            self._entities[9] = a9
            self._entities[10] = a10

        self.__write_all_to_file()

    def add_entity(self, entity):
        self.__read_all_from_file()
        super().add_entity(entity)
        self.__write_all_to_file()

    def update_entity(self, entity):
        self.__read_all_from_file()
        super().update_entity(entity)
        self.__write_all_to_file()

    def delete_by_id(self, address_id):
        self.__read_all_from_file()
        super().delete_by_id(address_id)
        self.__write_all_to_file()

    def get_all(self):
        self.__read_all_from_file()
        return super().get_all()
