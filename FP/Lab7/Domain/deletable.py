class Deletable:
    def __init__(self):
        self.__is_deleted = False

    def delete(self):
        self.__is_deleted = True

    def is_deleted(self):
        return self.__is_deleted
