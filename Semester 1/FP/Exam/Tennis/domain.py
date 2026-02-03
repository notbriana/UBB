class Player:

    def __init__(self, id_player, name, strength):

        self._id_player = id_player
        self._name = name
        self._strength = strength

    def get_id(self):
        return self._id_player

    def get_name(self):
        return self._name

    def get_strength(self):
        return self._strength

    def set_strength(self, value):
        self._strength = value

    def __str__(self):
        return f"{self._id_player}, {self._name}, {self._strength}"
