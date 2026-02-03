from domain import Address


class AddressTextFileRepo:

    def __init__(self, file_name):
        self._data = []
        self.__file_name = file_name
        self.__load()
        self.generate_addresses()

    def __load(self):
        try:
            with open(self.__file_name, "r") as f:
                self._data.clear()
                for line in f:
                    line = line.strip()
                    if line:
                        parts = line.split(",")
                        id = int(parts[0])
                        name = parts[1]
                        number = parts[2]
                        x = int(parts[3])
                        y = int(parts[4])
                        address = Address(id, name, number, x, y)
                        self._data.append(address)
        except FileNotFoundError:
        # If the file doesn't exist, start with an empty repository
            self._data = []


    def __save(self):
        with open(self.__file_name, "w") as f:
            for address in self._data:
                f.write(
                    f"{address.get_id()},{address.get_name()},{address.get_number()},{address.get_x()}, {address.get_y()}\n")

    def generate_addresses(self):
        a1 = Address(1, "Theodor Mihail", 10, 12, 20)
        a2 = Address(2, "Theodor Mihail", 15, 16, 30)
        a3 = Address(3, "Mihail Kogalniceanu", 1, 40, 45)
        a4 = Address(4, "Dorobantilor", 20, 50, 100)
        a5 = Address(5, "Dorobantilor", 22, 54, 100)
        a6 = Address(6, "Salciilor", 2, 2, 20)
        a7 = Address(7, "Salciilor", 50, 46, 18)
        a8 = Address(8, "Mihai Eminescu", 2, 90, 90)
        a9 = Address(9, "Mihai Eminescu", 3, 90, 92)
        a10 = Address(10, "Titulescu", 10, 10, 12)

        if len(self._data) == 0:
            self._data.append(a1)
            self._data.append(a2)
            self._data.append(a3)
            self._data.append(a4)
            self._data.append(a5)
            self._data.append(a6)
            self._data.append(a7)
            self._data.append(a8)
            self._data.append(a9)
            self._data.append(a10)

        self.__save()

    def add(self, address):
        # Validate address id
        if address.get_id() <= 0 or self.find(address.get_id()) is not None:
            raise ValueError("The id must be unique and a positive integer")

        # Validate name (must have at least 3 characters)
        if len(address.get_name()) < 3:
            raise ValueError("The street name must be at least 3 characters long")

        # Validate number (must be a positive integer and at most 100)
        if not (0 < address.get_number() <= 100):
            raise ValueError("The number must be a positive integer of at most 100")

        # Validate coordinates (must be within range)
        if not (-100 <= address.get_x() <= 100) or not (-100 <= address.get_y() <= 100):
            raise ValueError("Coordinates x and y must be between -100 and 100")

        # Add the address if all validations pass
        self._data.append(address)
        self.__save()

    def find(self, address_id):
        addresses = [a for a in self._data if a.get_id() == address_id]
        if len(addresses) != 0:
            return addresses[0]
        else:
            return None

    def get_all(self):
        return self._data
