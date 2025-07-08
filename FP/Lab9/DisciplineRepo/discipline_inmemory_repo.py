from DisciplineRepo.discipline_base_repo import DisciplineRepository


class DisciplineMemoryRepository(DisciplineRepository):
    def __init__(self):
        super().__init__()

    def add_entity(self, entity):
        super().add_entity(entity)

    def update_entity(self, entity):
        super().update_entity(entity)

    def delete_by_id(self, id_discipline):
        super().delete_by_id(id_discipline)

    def get_all(self):
        return super().get_all()
