USE SchoolDB;
GO

INSERT INTO dbo.Departments (Name, Office) VALUES  ('Computer Science', 'A101'), ('Mathematics', 'B201');
INSERT INTO dbo.Programs (DepartmentID, Name, DegreeType) VALUES (1, 'BSc Computer Science', 'BSc'), (2, 'BSc Mathematics', 'BSc');
INSERT INTO dbo.Rooms (Building, RoomNumber, Capacity) VALUES ('Main', '101', 40), ('Main', '102', 30);
INSERT INTO dbo.Teachers (DepartmentID, FirstName, LastName, Email) VALUES (1, 'Alice', 'Popescu', 'alice@school.local'), (2, 'Bogdan', 'Ionescu', 'bogdan@school.local');
INSERT INTO dbo.Courses (DepartmentID, CourseCode, Title, Credits) VALUES (1, 'CS101', 'Intro to Programming', 5), (2, 'MATH101', 'Calculus I', 5);
INSERT INTO dbo.Students (ProgramID, FirstName, LastName, DOB, EnrollmentDate, Email) VALUES (1, 'Ana', 'Georgescu', '2004-05-12', '2022-09-01', 'ana@example.com'), (1, 'Mihai', 'Dumitru', '2003-11-20', '2021-09-01', 'mihai@example.com');
INSERT INTO dbo.Classes (CourseID, TeacherID, RoomID, Semester, Year, Schedule, MaxCapacity) VALUES (1, 1, 1, 'Fall', 2024, 'Mon/Wed 10:00-11:30', 40), (2, 2, 2, 'Fall', 2024, 'Tue/Thu 09:00-10:30', 30);
INSERT INTO dbo.Assignments (ClassID, Title, DueDate, MaxPoints) VALUES (1, 'HW1 - Variables', '2024-09-15', 100), (1, 'HW2 - Loops', '2024-10-01', 100);
INSERT INTO dbo.Submissions (AssignmentID, StudentID, SubmittedAt, Score, Content) VALUES (1, 1, SYSUTCDATETIME(), 95, 'hw1.zip');
INSERT INTO dbo.Enrollments (StudentID, ClassID) VALUES (999, 1);
