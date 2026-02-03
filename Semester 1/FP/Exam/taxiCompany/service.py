import math

from domain import Address


class AddressService:
    def __init__(self, repo):
        self._repo = repo

    def add_address(self, id, name, number, x, y):
        """Add a new address to the system after validation"""
        address = Address(id, name, number, x, y)
        self._repo.add(address)

    def find_addresses_within_distance(self, x, y, d):
        """Find all addresses within a given distance from coordinates (x, y)"""
        array_addresses = []
        for address in self._repo.get_all():
            distance = math.sqrt((address.get_x() - x) ** 2 + (address.get_y() - y) ** 2)
            if distance <= d:
                array_addresses.append((address, distance))  # Returning address with its distance

        return array_addresses

    def find_optimal_taxi_station(self):
        """Find the optimal position for a taxi station"""
        total_x = sum(address.get_x() for address in self._repo.get_all())
        total_y = sum(address.get_y() for address in self._repo.get_all())
        avg_x = total_x / len(self._repo.get_all())
        avg_y = total_y / len(self._repo.get_all())

        if -100 <= avg_x <= 100 and -100 <= avg_y <= 100:
            return avg_x, avg_y
        return None

    def get_all_addresses(self):
        """Return all addresses to be displayed by UI"""
        return self._repo.get_all()
