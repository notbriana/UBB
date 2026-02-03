from service import BusTycoonService
from repository_bus.bus_text_file_repo import BusTextFile
from repository_route.route_text_file_repo import RouteTextFile

class BusTycoonUI:
    def __init__(self, service):
        self._service = service

    def run(self):
        """Displays the main menu and prompts user for an option."""
        while True:
            print("\nBus Tycoon Service Menu:")
            print("1. Display buses by route")
            print("2. Calculate distance for a bus")
            print("3. Display routes sorted by total mileage")
            print("4. Exit")

            choice = input("Enter your choice (1-4): ")

            if choice == "1":
                self.display_buses_by_route()
            elif choice == "2":
                self.calculate_distance_for_bus()
            elif choice == "3":
                self.display_routes_by_total_mileage()
            elif choice == "4":
                print("Exiting... Goodbye!")
                break
            else:
                print("Invalid choice! Please enter a number between 1 and 4.")

    def display_buses_by_route(self):
        """Displays all buses for a specific route."""
        route_code = input("Enter the route code: ")
        buses = self._service.display_buses_by_route(route_code)

        if not buses:
            print(f"No buses found for route code {route_code}.")
        else:
            print(f"\nBuses for route {route_code}:")
            for bus in buses:
                print(f"Bus ID: {bus.get_id()}, Model: {bus.get_model()}, Times Used: {bus.get_times_used_on_route()}")

    def calculate_distance_for_bus(self):
        """Calculates the total distance for a specific bus."""
        bus_id = int(input("Enter the bus ID: "))
        try:
            bus_info = self._service.calculate_distance(bus_id)
            print("\nBus Information and Distance:")
            for key, value in bus_info.items():
                print(f"{key}: {value}")
        except ValueError as e:
            print(e)

    def display_routes_by_total_mileage(self):
        """Displays routes sorted by the total mileage of buses on those routes."""
        routes = self._service.display_routes_by_total_mileage_on_that_route()

        if not routes:
            print("No routes found.")
        else:
            print("\nRoutes sorted by total mileage:")
            for route in routes:
                print(f"Route Code: {route['Route Code']}, Total Mileage: {route['Total Mileage']}")
