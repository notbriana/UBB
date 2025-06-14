class Discipline:
    """
    A class to represent a discipline with an ID and a name.
    """

    def __init__(self, discipline_id: int, name: str):

        self.__discipline_id = discipline_id
        self.__name = name

    def get_discipline_id(self):
        return self.__discipline_id

    def set_id(self, value):
        if not isinstance(value, int) or value <= 0:
            raise ValueError("Discipline ID must be a positive integer.")
        self.__discipline_id = value

    def get_name(self):
        return self.__name

    def set_name(self, value):
        if not isinstance(value, str) or not value.strip():
            raise ValueError("Name must be a non-empty string.")
        self.__name = value

    def __repr__(self):
        return f"Discipline(ID={self.__discipline_id}, Name={self.__name})"

    def __eq__(self, other):
        if isinstance(other, Discipline):
            return self.__discipline_id == other.__discipline_id and self.__name == other.__name
        return False