from repository import TextFileRepo
from service import Service
from ui import UI

repo = TextFileRepo("students.txt")
service = Service(repo)
ui = UI(service)
ui.run()