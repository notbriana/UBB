class Order:
    def __init__(self, id_driver, distance):
        """
        Initializes an Order instance.

        :param id_driver: The ID of the driver associated with the order.
        :param distance: The distance (in km) covered by the order.
        """
        self.__id_driver = id_driver
        self.__distance = distance
        self.__deleted = False

    def get_id_driver(self):
        """Returns the ID of the driver."""
        return self.__id_driver

    def set_id_driver(self, value):
        if not isinstance(value, int) or value <= 0:
            raise ValueError("Driver ID must be a positive integer.")
        self.__id_driver = value

    def get_distance(self):
        """Returns the distance of the order."""
        return self.__distance

    def set_distance(self, value):
        """Sets the distance for the order."""
        if not isinstance(value, (int, float)) or value < 1:
            raise ValueError("Distance must be a positive number.")
        self.__distance = value

    def mark_as_deleted(self):
        """Marks the driver as deleted."""
        self.__deleted = True

    def is_deleted(self):
        """Checks if the driver is marked as deleted."""
        return self.__deleted


    def __str__(self):
        """Provides a string representation of the order."""
        return f"{self.__id_driver}, {self.__distance}"
