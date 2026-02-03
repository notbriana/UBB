from UI import BusTycoonUI
from service import BusTycoonService
from repository_bus.bus_text_file_repo import BusTextFile
from repository_route.route_text_file_repo import RouteTextFile


def main():
    # Initialize the repository with a file name
    bus_repo = BusTextFile("buses.txt")
    route_repo = RouteTextFile("routes.txt")
    # Initialize the service with the repository
    service = BusTycoonService(bus_repo, route_repo)

    # Initialize the user interface with the service
    ui = BusTycoonUI(service)

    # Start the UI
    ui.run()


if __name__ == "__main__":
    main()
