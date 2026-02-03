from repository import AddressTextFileRepo
from service import AddressService
from ui import UI

repo = AddressTextFileRepo("addresses.txt")
service = AddressService(repo)
ui = UI(service)
ui.start()