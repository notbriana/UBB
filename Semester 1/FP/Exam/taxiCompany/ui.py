class UI:
    def __init__(self, service):
        self.service = service

    def start(self):
        """Start the user interface and continuously prompt for commands."""
        while True:
            self.print_menu()
            cmd = self.execute_command()
            if cmd == "X" or cmd == "x":
                print("Exiting the application. Goodbye!")
                exit()

    def print_menu(self):
        """Display the available commands to the user."""
        print("\nMain Menu:")
        print("A - Add an address")
        print("D - Display all addresses")
        print("F - Given a position, find the addresses within a distance")
        print("P - Find the optimal position for a new taxi station")
        print("X - Exit")

    def execute_command(self):
        """Execute the command based on user input."""
        cmd = input("<")
        cmd = cmd.upper()

        if cmd == "A":
            self.add_address()

        if cmd == "D":
            self.display_all_addresses()

        if cmd == "F":
            self.find_addresses_within_distance()

        if cmd == "P":
            self.find_optimal_taxi_station()

        return cmd

    def add_address(self):
        """Prompt the user for address details and add the address."""
        try:
            id = input("Enter the ID (positive integer): ")
            street_name = input("Enter the street name (at least 3 characters): ")
            street_number = input("Enter the street number (positive integer, max 100): ")
            x = input("Enter the x-coordinate (-100 to 100): ")
            y = input("Enter the y-coordinate (-100 to 100): ")

            # Validate input
            if id.isnumeric() and street_number.isnumeric() and x.isnumeric() and y.isnumeric():
                id = int(id)
                street_number = int(street_number)
                x = int(x)
                y = int(y)

                self.service.add_address(id, street_name, street_number, x, y)
                print("Address added successfully.")
            else:
                print("Invalid input! ID, street number, x, and y must be integers.")
        except ValueError as ve:
            print(f"Error: {ve}")

    def display_all_addresses(self):
        """Display all the addresses in the system."""
        addresses = self.service.get_all_addresses()
        if addresses:
            print("All registered addresses:")
            for address in addresses:
                print(address)
        else:
            print("No addresses found.")

    def find_addresses_within_distance(self):
        """Prompt the user for coordinates and distance, then display the results."""
        try:
            x = input("Enter the x-coordinate (-100 to 100): ")
            y = input("Enter the y-coordinate (-100 to 100): ")
            d = input("Enter the distance: ")

            if x.isnumeric() and y.isnumeric() and d.isnumeric():
                x = int(x)
                y = int(y)
                d = int(d)
                addresses_within_distance = self.service.find_addresses_within_distance(x, y, d)

                if addresses_within_distance:
                    self.display_addresses_with_distance(addresses_within_distance)
                else:
                    print(f"No addresses found within {d} distance from ({x}, {y}).")
            else:
                print("Invalid input! x, y, and distance must be integers.")
        except ValueError as e:
            print(f"Error: {e}")

    def display_addresses_with_distance(self, addresses_with_distance):
        """Display addresses with their distance."""
        print(f"Addresses within the specified distance:")
        for address, distance in addresses_with_distance:
            print(f"Address: {address}, Distance: {distance:.2f} units")

    def find_optimal_taxi_station(self):
        """Display the optimal location for a new taxi station."""
        optimal_position = self.service.find_optimal_taxi_station()
        if optimal_position:
            print(f"Optimal position for the new taxi station: x = {optimal_position[0]:.2f}, y = {optimal_position[1]:.2f}")
        else:
            print("The calculated position is out of range. Please try again.")

