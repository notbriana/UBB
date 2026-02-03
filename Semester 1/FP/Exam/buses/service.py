

class BusTycoonService:
    def __init__(self, bus_repo, route_repo):
        self._bus_repo = bus_repo
        self._route_repo = route_repo

    def display_buses_by_route(self, route_code):
        """
        Retrieves all buses assigned to a specific route.

        Parameters:
        - route_code: The code of the route.

        Returns:
        - A list of buses assigned to the specified route.
        """
        buses = self._bus_repo.get_all()
        buses_on_route = [bus for bus in buses if bus.get_route_code() == route_code]
        return buses_on_route

    def calculate_distance(self, bus_id):
        """
        Calculates the total distance traveled by a bus on its route and provides detailed information about the bus.

        Parameters:
        - bus_id: The ID of the bus.

        Returns:
        - A dictionary containing the total distance and detailed bus information.
        """
        # Retrieve the bus object by ID
        bus = self._bus_repo.search_by_id(bus_id)
        if not bus:
            raise ValueError(f"Bus with ID {bus_id} not found.")

        # Retrieve the route object using the bus's route code
        route = self._route_repo.search_by_id(bus.get_route_code())
        if not route:
            raise ValueError(f"Route with code {bus.get_route_code()} not found.")

        # Calculate the total distance traveled
        total_distance = route.get_length() * bus.get_times_used_on_route()

        # Create a detailed info dictionary
        return {
            "Bus ID": bus.get_id(),
            "Model": bus.get_model(),
            "Route Code": bus.get_route_code(),
            "Times Used on Route": bus.get_times_used_on_route(),
            "Total Distance Traveled": total_distance,
        }

    def display_routes_by_total_mileage_on_that_route(self):
        """
        Displays all routes sorted in ascending order by the total mileage traveled by buses on those routes.

        Returns:
        - A list of dictionaries containing route details and total mileage.
        """
        routes = self._route_repo.get_all()
        route_mileage = []

        for route in routes:
            total_mileage = sum(
                route.get_length() * bus.get_times_used_on_route()
                for bus in self.display_buses_by_route(route.get_route_code())
            )
            route_mileage.append({
                "Route Code": route.get_route_code(),
                "Total Mileage": total_mileage,
            })

        # Sort the routes by total mileage in ascending order
        route_mileage.sort(key=lambda x: x["Total Mileage"])
        return route_mileage
