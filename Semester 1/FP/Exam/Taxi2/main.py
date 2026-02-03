from driver_repo.driver_text_file_repo import DriverTextFileRepository
from address_repo.address_text_file_repo import AddressTextFileRepository
from service import TaxiService
from ui import TaxiAppUI


def main():
    # Initialize the repository with a file name
    drivers_repo = DriverTextFileRepository("drivers.txt")
    addresses_repo = AddressTextFileRepository("addresses.txt")
    # Initialize the service with the repository
    taxi_service = TaxiService(addresses_repo, drivers_repo)

    # Initialize the user interface with the service
    ui = TaxiAppUI(taxi_service)

    # Start the UI
    ui.run()


if __name__ == "__main__":
    main()
