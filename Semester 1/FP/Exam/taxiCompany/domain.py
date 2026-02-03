class Address:

    def __init__(self, id, name, number, x, y):

        self._id = id
        self._name = name
        self._number = number
        self._x = x
        self._y = y

    def get_id(self):
        return self._id

    def get_name(self):
        return self._name

    def get_number(self):
        return self._number

    def get_x(self):
        return self._x

    def get_y(self):
        return self._y

    def set_id(self, value):
        self._id = value

    def set_name(self, value):
        self._name = value

    def set_number(self, value):
        self._number = value

    def set_x(self, value):
        self._x = value

    def set_y(self, value):
        self._y = value

    def __str__(self):
        return f"{self._id}, {self._name}, {self._number}, {self._x}, {self._y} "