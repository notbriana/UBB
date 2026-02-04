import random
from datetime import date, timedelta
from faker import Faker
from domain import Hotel, Reservation

fake = Faker()

class FileError(Exception):
    pass

class HotelService:
    def __init__(self, hotel: Hotel):
        self.__hotel = hotel

    def load(self, filename='random_reservations.txt'):
        try:
            with open(filename, 'r') as file:
                if file.readable() and len(file.read()) == 0:
                    raise FileError("File is empty!")
                file.seek(0)
                for line in file:
                    data = line.strip().split(',')
                    try:
                        _id = int(data[0])
                        room = int(data[1])
                        name = data[2]
                        guests = int(data[3])
                        arrival_day = int(data[4])
                        arrival_mon = int(data[5])
                        dep_day = int(data[6])
                        dep_mon = int(data[7])
                        self.__hotel.add(_id, room, name, guests, arrival_day, arrival_mon, dep_day, dep_mon)
                    except ValueError as err:
                        raise FileError(err)
        except FileNotFoundError as err:
            raise FileError(err)

    def get_reservations_count(self, day: date):
        count = 0
        for res in self.__hotel.reservations.values():
            if res.arrival() <= day <= res.departure():
                count += 1
        return count

class ReservationGenerator:
    def __init__(self, hotel: Hotel):
        self.hotel = hotel
        self.names = [fake.name() for _ in range(100)]

    def generate_random_reservations(self, num_reservations=1000, filename='random_reservations.txt'):
        reservations = []
        for _ in range(num_reservations):
            _id = len(reservations) + 1
            room = random.choice(range(1, self.hotel.rooms.single + self.hotel.rooms.double + self.hotel.rooms.family + 1))
            name = random.choice(self.names)
            guests = random.randint(1, 4)
            arrival = fake.date_between(start_date='-1y', end_date='today')
            departure = arrival + timedelta(days=random.randint(1, 14))
            reservations.append(f"{_id},{room},{name},{guests},{arrival.day},{arrival.month},{departure.day},{departure.month}")

        with open(filename, 'w') as file:
            for reservation in reservations:
                file.write(reservation + '\n')