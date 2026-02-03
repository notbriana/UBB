class Address:
    def __init__(self, address_id, address_name, address_x, address_y):
        self._address_id = address_id
        self._address_name = address_name
        self._address_x = address_x
        self._address_y = address_y

    def get_address_id(self):
        return self._address_id
    def get_address_name(self):
        return self._address_name
    def get_address_x(self):
        return self._address_x
    def get_address_y(self):
        return self._address_y

    def __repr__(self):
        return f"Address(ID= {self._address_id}, Name= {self._address_name}, X= {self._address_x}, Y= {self._address_y}"