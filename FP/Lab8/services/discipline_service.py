from domain.discipline import Discipline

class DisciplineService:
    def __init__(self, discipline_repo, undo_services):
        self.__discipline_repo = discipline_repo
        self.__undo_services = undo_services

    def add_discipline(self, discipline_id, name):
        discipline = Discipline(discipline_id, name)
        self.__discipline_repo.add_entity(discipline)

    def remove_discipline(self, discipline_id):
        discipline = self.__discipline_repo.find_by_id(discipline_id)
        if not discipline:
            raise ValueError("Discipline not found.")
        self.__discipline_repo.delete_by_id(discipline_id)

    def update_discipline(self, discipline_id, new_name):
        discipline = self.__discipline_repo.find_by_id(discipline_id)
        if not discipline:
            raise ValueError("Discipline not found.")
        updated_discipline = Discipline(discipline_id, new_name)
        self.__discipline_repo.update(discipline_id, updated_discipline)

    def list_disciplines(self):
        return self.__discipline_repo.get_all()

    def search_disciplines(self, search_term):
        return [
            discipline
            for discipline in self.__discipline_repo.get_all()
            if search_term.lower() in discipline.get_name().lower() or str(discipline.get_discipline_id()) == search_term
        ]

    def find_by_id(self, discipline_id):
        return self.__discipline_repo.find_by_id(discipline_id)
