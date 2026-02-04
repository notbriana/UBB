import random
from domain import Taxi

class Service:
    def __init__(self, repo):
        self._repo = repo

    def repo(self):
        return self._repo

    def manhattan_distance(self, x1, y1, x2, y2):
        return abs(x2 - x1) + abs(y2 - y1)

    def generate_entities(self):
        taxis = []
        for i in range(10):
            while True:
                x, y = random.randint(0, 100), random.randint(0, 100)
                if all(self.manhattan_distance(x, y, taxi.get_x(), taxi.get_y()) > 5 for taxi in taxis):
                    taxi = Taxi(i + 1, x, y, 0)
                    taxis.append(taxi)
                    break
        for taxi in taxis:
            self._repo.add(taxi)

