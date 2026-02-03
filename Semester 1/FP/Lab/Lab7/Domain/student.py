from Domain.deletable import Deletable
from Domain.identifiable import Identifiable

class Student(Identifiable, Deletable):

    def __init__(self, id_student, name, group):
        Deletable.__init__(self)
        Identifiable.__init__(self, id_student)
        self.__id_student = id_student
        self.__name = name
        self.__group = group

    def get_id_student(self):
        return self.__id_student

    def get_name(self):
        return self.__name

    def get_group(self):
        return self.__group

    def __str__(self):
        return f"ID: {self.get_id_entity()}, Name: {self.__name}, Group: {self.__group}"

