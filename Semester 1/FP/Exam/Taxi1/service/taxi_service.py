from domain.order_domain import Order


class TaxiService:

    def __init__(self, driver_repo, order_repo):
        self.__driver_repo = driver_repo
        self.__order_repo = order_repo

    def add_order(self, id_driver, distance):
        """
        Adds a new order for a specific driver.

        :param id_driver: The ID of the driver.
        :param distance: The distance of the order in kilometers.
        :raises ValueError: If the distance is less than 1 km or the driver does not exist.
        """
        if distance < 1:
            raise ValueError("Distance must be at least 1 km.")
        driver = self.__driver_repo.search_by_id(id_driver)
        if not driver:
            raise ValueError("Driver does not exist.")
        order = Order(id_driver, distance)
        self.__order_repo.add_order(order)

    def display_all(self):
        """
        Displays all drivers with their respective orders.

        :return: A list of dictionaries containing driver details and their orders.
        """
        results = []
        drivers = self.__driver_repo.get_all()

        for driver in drivers:
            driver_info = {
                "id": driver.get_id_driver(),
                "name": driver.get_name(),
                "orders": []
            }

            # Fetch all orders for the driver
            orders = self.__order_repo.get_all_by_id(driver.get_id_driver())
            if orders:  # Ensure orders is iterable
                for order in orders:
                    driver_info["orders"].append({
                        "distance": order.get_distance()
                    })

            results.append(driver_info)

        return results

    def calculate_income(self, id_driver):
        """
        Calculates the total income for a specific driver.

        :param id_driver: The ID of the driver.
        :return: The total income (float).
        :raises ValueError: If the driver does not exist or has no orders.
        """
        rate_per_km = 2.5
        driver = self.__driver_repo.search_by_id(id_driver)
        if not driver:
            raise ValueError("Driver does not exist.")

        orders = self.__order_repo.get_all_by_id(id_driver)
        if not orders:
            raise ValueError("Driver has no orders.")

        total_distance = sum(order.get_distance() for order in orders)
        income = total_distance * rate_per_km
        return income
