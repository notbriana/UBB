from Repositories.student_text_file_repo import StudentTextFileRepository
from Repositories.student_binary_file_repo import StudentBinaryFileRepository
from Services.student_service import StudentService
from UI.ui import UI
from Domain.student import Student
from random import randint

def generate_students():
    names = ["Alice", "Bob", "Charlie", "Diana", "Eve", "Frank", "Grace", "Hank", "Ivy", "Jack"]
    students = []
    for i in range(10):
        student_id = i + 1
        name = names[i % len(names)]
        group = randint(1, 5)
        students.append(Student(student_id, name, group))
    return students

if __name__ == "__main__":
    # Choose either text or binary repository
    # repo = StudentTextFileRepository("students.txt") #nu merge
    repo = StudentBinaryFileRepository("students.bin")

    if not repo.get_all() or repo.get_all() == []:
        students = generate_students()
        for student in students:
            repo.add_entity(student)

    service = StudentService(repo)
    ui = UI(service)
    ui.display_menu()
