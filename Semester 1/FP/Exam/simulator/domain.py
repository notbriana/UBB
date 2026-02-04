class Taxi:

    def __init__(self, id, x, y, total_fares):
        self._id = id
        self._x = x
        self._y = y
        self._total_fares = total_fares

    def get_id(self):
        return self._id

    def get_x(self):
        return self._x

    def get_y(self):
        return self._y

    def get_total_fares(self):
        return self._total_fares

    def set_x(self, value):
        self._x = value

    def set_y(self, value):
        self._y = value

    def set_total_fares(self, value):
        self._total_fares = value

    def __str__(self):
        return f"{self._id},{self._x},{self._y},{self._total_fares}"