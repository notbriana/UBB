class Driver:
    def __init__(self, name, x, y):
        self._name = name
        self._x = x
        self._y = y

    def get_name(self):
        return self._name

    def get_position_x(self):
        return self._x

    def get_position_y(self):
        return self._y

    def __repr__(self):
        return f"Driver(Name= {self._name}, x= {self._x}, y= {self._y}"