USE SchoolDB;
GO

INSERT INTO dbo.Departments (Name, Office)
VALUES ('Computer Science', 'A101'),
       ('Mathematics', 'B201'),
       ('Biology', 'C301');
GO

INSERT INTO dbo.Programs (DepartmentID, Name, DegreeType)
VALUES (1, 'BSc Computer Science', 'BSc'),
       (2, 'BSc Mathematics', 'BSc'),
       (3, 'BSc Biology', 'BSc');
GO

INSERT INTO dbo.Rooms (Building, RoomNumber, Capacity)
VALUES ('Main', '101', 40),
       ('Main', '102', 30),
       ('North', '201', 50),
	   ('East', '301', 35);
GO

INSERT INTO dbo.Teachers (DepartmentID, FirstName, LastName, Email)
VALUES (1, 'Alice', 'Popescu', 'alice@school.com'),
       (2, 'Bogdan', 'Ionescu', 'bogdan@school.com'),
       (3, 'Catalin', 'Marin', 'catalin@school.com');
GO

INSERT INTO dbo.Courses (DepartmentID, CourseCode, Title, Credits)
VALUES (1, 'CS101', 'Intro to Programming', 5),
       (2, 'MATH101', 'Calculus I', 5),
       (3, 'BIO101', 'Intro to Biology', 4);
GO

INSERT INTO dbo.Students (ProgramID, FirstName, LastName, DOB, EnrollmentDate, Email)
VALUES (1, 'Ana', 'Georgescu', '2004-05-12', '2022-09-01', 'ana@example.com'),
       (1, 'Mihai', 'Dumitru', '2003-11-20', '2021-09-01', 'mihai@example.com'),
       (3, 'Ioana', 'Pop', '2004-03-02', '2023-09-01', 'ioana@example.com'),
       (3, 'Laura', 'Dumitrescu', '2004-02-20', '2023-09-01', 'laura@example.com');
GO

INSERT INTO dbo.Classes (CourseID, TeacherID, RoomID, Semester, Year, Schedule, MaxCapacity)
VALUES (1, 1, 1, 'Fall', 2024, 'Mon/Wed 10:00-11:30', 40),
       (2, 2, 2, 'Fall', 2024, 'Tue/Thu 09:00-10:30', 30),
       (3, 3, 3, 'Spring', 2025, 'Mon/Wed 08:00-09:30', 50);
GO

INSERT INTO dbo.Enrollments (StudentID, ClassID)
VALUES (1, 1),
       (2, 1),
       (2, 2),
       (3, 3),
       (4, 3);
GO

INSERT INTO dbo.Assignments (ClassID, Title, DueDate)
VALUES (1, 'HW1 - Variables', '2024-09-15'),
       (1, 'HW2 - Loops', '2024-10-01'),
       (2, 'Calculus Homework 1', '2024-09-20'),
       (3, 'Lab1 - Cells', '2025-03-10');
GO

INSERT INTO dbo.Submissions (AssignmentID, StudentID, Score, Content)
VALUES (1, 1, 95, 'hw1.zip'),
       (2, 1, 88, 'hw2.zip'),
       (3, 2, 90, 'calc1.pdf'),
       (4, 3, 85, 'lab1.zip');
GO

INSERT INTO dbo.TeacherCourses (TeacherID, CourseID, Role)
VALUES (1, 1, 'Main'),
       (2, 2, 'Main'),
       (3, 3, 'Main'),
       (2, 1, 'Assistant');  
GO

INSERT INTO dbo.Programs (DepartmentID, Name, DegreeType) VALUES (999, 'Fake Program', 'BSc');

