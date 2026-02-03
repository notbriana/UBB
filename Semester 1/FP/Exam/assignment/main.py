from repository import TextFileRepo
from service import Service
from UI import UI

def main():
    repo = TextFileRepo("assignments.txt")
    service = Service(repo)
    ui = UI(service)
    ui.run()

if __name__ == "__main__":
    main()