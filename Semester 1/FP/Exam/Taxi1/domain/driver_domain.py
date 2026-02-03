class Driver:
    def __init__(self, id_driver, name):
        self._id_driver = id_driver
        self._name = name
        self._deleted = False

    def get_id_driver(self):
        return self._id_driver

    def set_id_driver(self, value):
        if not isinstance(value, int) or value <= 0:
            raise ValueError("Driver ID must be a positive integer.")
        self._id_driver = value

    def get_name(self):
        return self._name

    def set_name(self, value):
        if not isinstance(value, str) or not value.strip():
            raise ValueError("Name must be a non-empty string.")
        self._name = value

    def mark_as_deleted(self):
        """Marks the driver as deleted."""
        self._deleted = True

    def is_deleted(self):
        """Checks if the driver is marked as deleted."""
        return self._deleted


    def __str__(self):
        return f"{self.__id_driver}, {self.__name}"
