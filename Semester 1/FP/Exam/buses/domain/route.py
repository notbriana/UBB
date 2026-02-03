class Route:
    def __init__(self, route_code, length):
        self._route_code = route_code
        self._length = length

    def get_route_code(self):
        return self._route_code

    def get_length(self):
        return self._length

    def set_route_code(self, value):
        self._route_code = value

    def set_length(self, value):
        self._length = value

    def __str__(self):
        return f"{self._route_code},{self._length}"