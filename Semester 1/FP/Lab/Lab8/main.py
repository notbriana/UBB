from services.student_service import StudentService
from services.discipline_service import DisciplineService
from services.grade_service import GradeService
from ui.console import Console
from faker import Faker
from services.undo_services import UndoServices
from settings import Settings

def main():
    settings = Settings()
    student_repo = settings.get_student_repo()
    discipline_repo = settings.get_discipline_repo()
    grade_repo = settings.get_grade_repo()
    undo_service = UndoServices()    
    # Create services
    student_service = StudentService(student_repo, grade_repo, undo_service)
    discipline_service = DisciplineService(discipline_repo, undo_service)
    grade_service = GradeService(grade_repo, student_repo, discipline_repo, undo_service)

    faker = Faker()

    # Generate and add fake students and disciplines

    #for i in range(1, 21):
    #    student_service.add_student(i, faker.name())
    #    discipline_service.add_discipline(i, faker.word().capitalize())

    console = Console(student_service, discipline_service, grade_service, undo_service)
    console.run()

main()