# Assuming you have a Player class already implemented in the domain
from domain import Player
from repository import TextFileRepo
from service import TournamentService
from ui import TournamentUI

# Initialize repository and service
repo = TextFileRepo("players.txt")
service = TournamentService(repo)
ui = TournamentUI(service, repo)

# Run the UI
ui.run()
