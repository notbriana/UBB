from service.taxi_service import TaxiService
from driver_repo.driver_text_file_repo import DriverTextFileRepository
from order_repo.order_text_file_repo import OrderTextFileRepository

class Console:
    def __init__(self, taxi_service):
        self.__taxi_service = taxi_service

    def run(self):
        while True:
            print("\nMenu:")
            print("2. Manage Orders")
            print("3. View All Drivers and Their Orders")
            print("4. Calculate Income for Driver")
            print("0. Exit")
            option = input("Choose an option: ").strip()

            if option == "2":
                self._manage_orders()
            elif option == "3":
                self._view_all_drivers_and_orders()
            elif option == "4":
                self._calculate_income_for_driver()
            elif option == "0":
                print("Exiting program.")
                break
            else:
                print("Invalid option. Please try again.")

    def _manage_orders(self):
        while True:
            print("\nOrder Management:")
            print("1. Add Order")
            print("0. Back to Main Menu")
            option = input("Choose an option: ").strip()

            if option == "1":
                driver_id = int(input("Enter Driver ID for the order: "))
                distance = float(input("Enter distance in km: "))
                try:
                    self.__taxi_service.add_order(driver_id, distance)
                    print("Order added successfully.")
                except ValueError as e:
                    print(e)

            elif option == "0":
                break
            else:
                print("Invalid option. Please try again.")

    def _view_all_drivers_and_orders(self):
        orders = self.__taxi_service.display_all()
        for driver in orders:
            driver_id = driver["id"]
            driver_name = driver["name"]
            orders_list = driver["orders"]
            print(f"Driver {driver_id} - {driver_name}")
            for order in orders_list:
                print(f"\tOrder: {order['distance']} km")

    def _calculate_income_for_driver(self):
        driver_id = int(input("Enter Driver ID to calculate income: "))
        try:
            income = self.__taxi_service.calculate_income(driver_id)
            print(f"Driver {driver_id}'s total income: ${income:.2f}")
        except ValueError as e:
            print(e)


if __name__ == "__main__":
    driver_repo = DriverTextFileRepository("drivers.txt")
    order_repo = OrderTextFileRepository("orders.txt")
    taxi_service = TaxiService(driver_repo, order_repo)
    console = Console(taxi_service)
    console.run()
