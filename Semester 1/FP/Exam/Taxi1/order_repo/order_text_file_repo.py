from order_repo.order_base_file_repo import OrderRepository
from domain.order_domain import Order


class OrderTextFileRepository(OrderRepository):
    def __init__(self, file_path):
        super().__init__()
        self.__file_path = file_path
        self.generate_orders()

    def __read_all_from_file(self):
        try:
            with open(self.__file_path, "r") as f:
                self._entities.clear()
                for line in f:
                    parts = line.strip().split(",")
                    id_driver = int(parts[0])
                    distance = int(parts[1])
                    order = Order(id_driver, distance)
                    self._entities[id_driver] = order
        except FileNotFoundError:
            self._entities = {}

    def __write_all_to_file(self):
        with open(self.__file_path, "w") as f:
            for driver in self._entities.values():
                f.write(f"{driver.get_id_driver()},{driver.get_distance()}\n")

    def generate_orders(self):
        """
        Generate a predefined set of orders and populate the repository.
        """
        o1 = Order(1, 15)
        o2 = Order(2, 25)
        o3 = Order(3, 30)
        o4 = Order(4, 20)
        o5 = Order(5, 35)
        o6 = Order(6, 10)
        o7 = Order(7, 50)
        o8 = Order(8, 40)
        o9 = Order(9, 5)
        o10 = Order(10, 45)

        if len(self._entities) == 0:  # Ensures orders are only added if repository is empty
            self._entities[1] = o1
            self._entities[2] = o2
            self._entities[3] = o3
            self._entities[4] = o4
            self._entities[5] = o5
            self._entities[6] = o6
            self._entities[7] = o7
            self._entities[8] = o8
            self._entities[9] = o9
            self._entities[10] = o10

        self.__write_all_to_file()

    def add_entity(self, entity):
        self.__read_all_from_file()
        super().add_order(entity)
        self.__write_all_to_file()

    def update_entity(self, entity):
        self.__read_all_from_file()
        super().update_order(entity)
        self.__write_all_to_file()

    def delete_by_id(self, id_driver):
        self.__read_all_from_file()
        super().delete_by_id(id_driver)
        self.__write_all_to_file()

    def get_all(self):
        self.__read_all_from_file()
        return super().get_all()
