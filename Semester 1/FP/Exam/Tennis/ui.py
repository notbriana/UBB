class TournamentUI:
    def __init__(self, service, repo):
        self._service = service
        self._repo = repo

    def print_menu(self):
        print("\nTournament Menu:")
        print("1. Start the Tournament")
        print("2. Display Players")
        print("3. Exit")

    def start_tournament(self):
        # Get all players and start the qualification round
        players = self._repo.get_all()
        round_num = 1

        # Qualifying round
        remaining_players, eliminated_players = self._service.qualifying_round(players)
        print("\nQualification Round")
        self.play_round(remaining_players, round_num)

    def play_round(self, remaining_players, round_num):
        # Play until we have one winner
        while len(remaining_players) > 1:
            round_name = f"Round {round_num}: "
            if len(remaining_players) == 4:
                round_name = "Last 4"
            elif len(remaining_players) == 8:
                round_name = "Last 8"
            print(f"\n{round_name}")

            # Randomly pair the players
            pairings = self._service.create_pairings(remaining_players)
            for pair in pairings:
                self.display_game(pair)
                winner_choice = input("Enter the winner (1 or 2): ").strip()
                self.handle_winner(winner_choice, pair)

            # Update remaining players for the next round
            remaining_players = self.get_remaining_players(pairings)
            round_num += 1

        # The tournament ends when there is one player left
        print("\nThe tournament has ended!")
        print(f"Winner: {remaining_players[0].get_name()} with strength {remaining_players[0].get_strength()}")

    def display_players(self):
        # Display all players and their current strengths
        players = self._service.display_players()
        if not players:
            print("No players found.")
        else:
            print("\nPlayers (sorted by strength):")
            for player in players:
                print(f"ID: {player.get_id()}, Name: {player.get_name()}, Strength: {player.get_strength()}")

    def display_game(self, pair):
        print(f"Game: {pair[0].get_name()} (Strength: {pair[0].get_strength()}) vs {pair[1].get_name()} (Strength: {pair[1].get_strength()})")

    def handle_winner(self, winner_choice, pair):
        if winner_choice == '1':
            winner = pair[0]
        elif winner_choice == '2':
            winner = pair[1]
        else:
            print("Invalid input! Please enter 1 or 2.")
            return

        self._service.update_winner(winner)
        print(f"{winner.get_name()} wins! Updated strength: {winner.get_strength()}")

    def get_remaining_players(self, pairings):
        remaining_players = []
        for pair in pairings:
            winner_choice = input(f"Enter the winner for {pair[0].get_name()} vs {pair[1].get_name()}: ").strip()
            if winner_choice == '1':
                winner = pair[0]
            elif winner_choice == '2':
                winner = pair[1]
            else:
                print("Invalid input! Try again.")
                continue
            remaining_players.append(winner)
        return remaining_players

    def run(self):
        while True:
            self.print_menu()
            choice = input("Choose an option: ").strip()
            if choice == "1":
                self.start_tournament()
            elif choice == "2":
                self.display_players()
            elif choice == "3":
                print("Exiting tournament.")
                break
            else:
                print("Invalid choice. Please try again.")
