class TextFileRoom:
    def __init__(self, file_name):
        self.file_name = file_name
        self.rooms = {}

    def read_rooms(self, file_name = 'rooms.txt'):
        try:
            with open(file_name, 'r') as f:
                for line in f:
                    room_number, room_type = line.strip().split(',')
                    self.rooms[room_number] = room_type
        except FileNotFoundError:
            print('File not found')

class TextFileReservation:
    def __init__(self, file_name):
        self.file_name = file_name
        self.reservations = {}

    def read_reservations(self, file_name = 'reservations.txt'):
        try:
            with open(file_name, 'r') as f:
                for line in f:
                    id, room_number, name, number_guests, arrival_day, arrival_month, departure_day, departure_month = line.strip().split(',')
                    self.reservations[id] = (room_number, name, number_guests, arrival_day, arrival_month, departure_day, departure_month)
        except FileNotFoundError:
            print('File not found')

