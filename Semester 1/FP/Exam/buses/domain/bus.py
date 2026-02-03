class Bus:

    def __init__(self, bus_id, route_code, model, times_used_on_route):
        self._bus_id = bus_id
        self._route_code = route_code
        self._model = model
        self._times_used_on_route = times_used_on_route

    def get_id(self):
        return self._bus_id

    def get_route_code(self):
        return self._route_code

    def get_model(self):
        return self._model

    def get_times_used_on_route(self):
        return self._times_used_on_route

    def set_id(self, value):
        self._bus_id = value

    def set_route_code(self, value):
        self._route_code = value

    def set_model(self, value):
        self._model = value

    def set_times_used_on_route(self, value):
        self._times_used_on_route = value

    def __str__(self):
        return f"{self._bus_id},{self._route_code},{self._model},{self._times_used_on_route}"