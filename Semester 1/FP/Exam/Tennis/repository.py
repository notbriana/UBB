from domain import Player

class TextFileRepo:
    def __init__(self, file_name):
        self._data = []
        self.__file_name = file_name
        self.__load()
        self.generate_players()

    def __load(self):
        try:
            with open(self.__file_name, "r") as f:
                self._data.clear()
                for line in f:
                    line = line.strip()
                    if line:  # Skip empty lines
                        parts = line.split(",")
                        id = int(parts[0])
                        name = parts[1]
                        strength = int(parts[2])
                        player = Player(id, name, strength)
                        self._data.append(player)
        except FileNotFoundError:
            # If the file doesn't exist, start with an empty repository
            self._data = []

    def __save(self):
        with open(self.__file_name, "w") as f:
            for player in self._data:
                f.write(
                    f"{player.get_id()},{player.get_name()},{player.get_strength()}\n")

    def generate_players(self):
        a1 = Player(1, "Theodor Mihail", 24)
        a2 = Player(2, "Ana Blandiana", 55)
        a3 = Player(3, "Corina Escu", 24)
        a4 = Player(4, "Lara Jula", 67)
        a5 = Player(5, "Doru Flaore", 78)
        a6 = Player(6, "Denisa Emrich", 58)
        a7 = Player(7, "Adela Haban", 48)
        a8 = Player(8, "Mihai Emil", 30)
        a9 = Player(9, "Mihai Eminescu", 24)
        a10 = Player(10, "Titulescu Noe", 33)

        if len(self._data) == 0:
            self._data.append(a1)
            self._data.append(a2)
            self._data.append(a3)
            self._data.append(a4)
            self._data.append(a5)
            self._data.append(a6)
            self._data.append(a7)
            self._data.append(a8)
            self._data.append(a9)
            self._data.append(a10)

        self.__save()

    def add(self, player):
        if player.get_id() < 0 or self.find(player.get_id()) is not None:
            raise ValueError("The id must be unique and a positive integer")
        else:
            self._data.append(player)
        self.__save()

    def update(self, player):
        """
        Updates an existing player in the collection.

        :param player: The player object with updated information.
        :raises ValueError: If the player's name is too short or the player does not exist in the collection.
        """
        # Validate name length
        if player.get_id() < 0 or self.find(player.get_id()) is not None:
            raise ValueError("The id must be unique and a positive integer")
        # Find the existing student by ID
        for i, existing_player in enumerate(self._data):
            if existing_player.get_id() == player.get_id():
                # Replace the existing student with the updated one
                self._data[i] = player
                self.__save()  # Persist changes
                return

        # Raise error if student not found
        raise ValueError("player with the given ID does not exist.")

    def find(self, player_id):
        players = [a for a in self._data if a.get_id() == player_id]
        if len(players) != 0:
            return players[0]
        else:
            return None

    def get_all(self):
        return self._data