class TaxiAppUI:
    def __init__(self, taxi_service):
        self.taxi_service = taxi_service

    def display_addresses_and_drivers(self):
        addresses, drivers = self.taxi_service.get_addresses_and_drivers_sorted()
        print("\n--- Addresses ---")
        for address in addresses:
            print(address)
        print("\n--- Drivers ---")
        for driver in drivers:
            print(driver)

    def display_drivers_by_distance(self, address_id):
        address = self.taxi_service.find_address(address_id)
        if address:
            drivers = self.taxi_service.get_all_drivers_sorted()
            sorted_drivers = self.taxi_service.drivers_sorted_by_distance(address, drivers)
            print(f"\nDrivers sorted by distance to {address.get_address_name()}:")
            for driver, distance in sorted_drivers:
                print(f"{driver.get_name()} - Distance: {distance}")
        else:
            print(f"Address with ID {address_id} not found.")

    def display_closest_drivers_for_all_addresses(self):
        try:
            closest_drivers = self.taxi_service.closest_drivers_for_all_addresses()

            print("\nClosest drivers for each address (sorted by decreasing distance):")
            for address, driver, distance in closest_drivers:
                print(f"Address: {address.get_address_name()}, Driver: {driver.get_name()}, Distance: {distance}")
        except Exception as e:
            print(f"An error occurred: {str(e)}")
            
    def run(self):
        """Main method to run the UI loop."""
        while True:
            # Display main menu
            print("\n--- Taxi App Menu ---")
            print("1. Display all addresses and drivers")
            print("2. Display drivers sorted by distance to an address")
            print("3. Display closest driver for each address")
            print("4. Exit")

            choice = input("Choose an option: ")

            if choice == '1':
                self.display_addresses_and_drivers()

            elif choice == '2':
                address_id = int(input("Enter the address ID: "))
                self.display_drivers_by_distance(address_id)

            elif choice == '3':
                self.display_closest_drivers_for_all_addresses()

            elif choice == '4':
                print("Exiting the app.")
                break

            else:
                print("Invalid option. Please try again.")
