class TaxiService:
    def __init__(self, address_repo, driver_repo):
        self._address_repo = address_repo
        self._driver_repo = driver_repo

    def get_all_addresses_sorted(self):
        """Retrieve all addresses sorted by their names."""
        addresses = self._address_repo.get_all()
        return sorted(addresses, key=lambda address: address.get_address_name())


    def get_all_drivers_sorted(self):
        """Retrieve all drivers sorted by their names."""
        drivers = self._driver_repo.get_all()
        return sorted(drivers, key=lambda driver: driver.get_name())

    def get_addresses_and_drivers_sorted(self):
        """Retrieve all addresses and drivers sorted by their names."""
        addresses = self.get_all_addresses_sorted()
        drivers = self.get_all_drivers_sorted()
        return addresses, drivers

    def find_address(self, address_id):
        """
        This function finds the address by id
        :param address_id: the address id to search for
        :return: the address or None if not found
        """
        return self._address_repo.find_by_id(address_id)

    def manhattan_distance(self, x1, y1, x2, y2):
        """Calculate Manhattan distance."""
        return abs(x1 - x2) + abs(y1 - y2)

    def drivers_sorted_by_distance(self, address, drivers):
        """
        Sort drivers by their distance to the given address using the Manhattan distance formula.
        :param address: the address to calculate distances to
        :param drivers: list of drivers to sort
        :return: list of tuples (driver, distance) sorted by distance
        """
        distances = [(driver, self.manhattan_distance(address.get_address_x(), address.get_address_y(), driver.get_position_x(), driver.get_position_y())) for driver in drivers]
        return sorted(distances, key=lambda item: item[1])

    def closest_drivers_for_all_addresses(self):
        """
        Find the closest driver for each address.
        Returns a list of tuples: (address, driver, distance), sorted by decreasing distance.
        """
        addresses = self.get_all_addresses_sorted()
        drivers = self.get_all_drivers_sorted()
        closest_drivers = []

        for address in addresses:
            sorted_drivers = self.drivers_sorted_by_distance(address, drivers)
            closest_driver, distance = sorted_drivers[0]  # Closest driver and its distance
            closest_drivers.append((address, closest_driver, distance))

        # Sort by distance in decreasing order
        closest_drivers.sort(key=lambda x: x[2], reverse=True)

        return closest_drivers