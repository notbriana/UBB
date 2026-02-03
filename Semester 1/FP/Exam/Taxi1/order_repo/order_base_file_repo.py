class OrderRepository:

    def __init__(self):
        self._entities = {}

    def add_order(self, entity):
        """
        Adds a new order to the other orders already existing at a driver.

        :param entity: The Order object to add.
        """
        if entity.get_id_driver() not in self._entities:
            raise ValueError("Driver does not exist!")
        self._entities[entity.get_id_driver()] = entity

    def update_order(self, entity):
        if entity.get_id_driver() not in self._entities:
            raise ValueError("Driver does not exist!")
        # Find and update the specific order (if necessary)

    def search_by_id(self, id_driver):
        if id_driver not in self._entities:
            raise ValueError("Driver doesn't exist!")
        return self._entities[id_driver]

    def delete_by_id(self, id_driver):
        if id_driver not in self._entities:
            raise ValueError("Driver does not exist!")
        del self._entities[id_driver]

    def get_all(self):
        return self._entities

    def get_all_by_id(self, id_driver):
        """
        Retrieves all orders for a specific driver.

        :param id_driver: The ID of the driver.
        :return: A list of orders for the driver.
        """
        return [order for order in self._entities.values() if order.get_id_driver() == id_driver]

