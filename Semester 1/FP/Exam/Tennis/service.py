import random
from domain import Player  # Assuming Player is correctly defined in the domain module

class TournamentService:
    def __init__(self, player_repo):
        self._player_repo = player_repo

    def display_players(self):
        players = self._player_repo.get_all()
        return self.sort_players_by_strength(players)

    def sort_players_by_strength(self, players):
        # Sort players by strength in descending order
        sorted_players = sorted(players, key=self.sort_by_strength, reverse=True)
        return sorted_players

    def sort_by_strength(self, player):
        return player.get_strength()

    def qualifying_round(self, players):
        sorted_players = self.sort_players_by_strength(players)
        num_players = len(sorted_players)

        # Ensure players count is a power of 2
        while num_players % 2 == 0 and num_players > 1:
            num_players //= 2

        if num_players == 1:
            return sorted_players
        else:
            # Find closest power of 2 less than total number of players
            closest_power_of_2 = 1
            while closest_power_of_2 * 2 <= len(sorted_players):
                closest_power_of_2 *= 2

            # Calculate and eliminate extra players
            extra_players = len(sorted_players) - closest_power_of_2
            eliminated_players = sorted_players[len(sorted_players) - extra_players:]
            remaining_players = sorted_players[:len(sorted_players) - extra_players]

            return remaining_players, eliminated_players

    def create_pairings(self, players):
        random.shuffle(players)
        pairings = [(players[i], players[i + 1]) for i in range(0, len(players), 2)]
        return pairings

    def update_winner(self, player):
        player.set_strength(player.get_strength() + 1)
        self._player_repo.update(player)
