from driver_repo.driver_text_file_repo import DriverTextFileRepository
from order_repo.order_text_file_repo import OrderTextFileRepository
from service.taxi_service import TaxiService
from UI import Console


def main():
    # Initialize the repository with a file name
    drivers_repo = DriverTextFileRepository("drivers.txt")
    orders_repo = OrderTextFileRepository("orders.txt")
    # Initialize the service with the repository
    taxi_service = TaxiService(drivers_repo, orders_repo)

    # Initialize the user interface with the service
    ui = Console(taxi_service)

    # Start the UI
    ui.run()


if __name__ == "__main__":
    main()
