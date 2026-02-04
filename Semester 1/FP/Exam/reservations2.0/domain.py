class Room:
    def __init__(self, room_number, room_type):
        self.room_number = room_number
        self.room_type = room_type

    def __repr__(self):
        return f'Room({self.room_number}, {self.room_type})'

class Reservation:
    def __init__(self, id, room_number, name, number_guests, arrival_day, arrival_month, departure_day, departure_month):
        self.id = id
        self.room_number = room_number
        self.name = name
        self.number_guests = number_guests
        self.arrival_day = arrival_day
        self.arrival_month = arrival_month
        self.departure_day = departure_day
        self.departure_month = departure_month

    def __repr__(self):
        return f'Reservation({self.id}, {self.room_number}, {self.name}, {self.number_guests}, {self.arrival_day}, {self.arrival_month}, {self.departure_day}, {self.departure_month})'
    

