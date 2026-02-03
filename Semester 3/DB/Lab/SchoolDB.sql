USE SchoolDB
GO

CREATE TABLE dbo.Departments (
	DepartmentID INT IDENTITY(1,1) PRIMARY KEY,
	Name NVARCHAR(100) NOT NULL UNIQUE,
	Office NVARCHAR(50) NULL
);
GO

CREATE TABLE dbo.Programs (
    ProgramID INT IDENTITY(1,1) PRIMARY KEY,
    DepartmentID INT NOT NULL,
    Name NVARCHAR(120) NOT NULL,
    DegreeType NVARCHAR(30) NULL,
    CONSTRAINT FK_Programs_Department FOREIGN KEY (DepartmentID) REFERENCES dbo.Departments(DepartmentID)
);
GO

CREATE TABLE dbo.Rooms (
    RoomID INT IDENTITY(1,1) PRIMARY KEY,
    Building NVARCHAR(50) NOT NULL,
    RoomNumber NVARCHAR(20) NOT NULL,
    Capacity INT NOT NULL CHECK (Capacity >= 0)
);
GO

CREATE TABLE dbo.Teachers (
    TeacherID INT IDENTITY(1,1) PRIMARY KEY,
    DepartmentID INT NOT NULL,
    FirstName NVARCHAR(50) NOT NULL,
    LastName NVARCHAR(50) NOT NULL,
    Email NVARCHAR(150) NULL UNIQUE,
    HireDate DATE NULL,
    IsActive BIT NOT NULL DEFAULT 1,
    CONSTRAINT FK_Teachers_Department FOREIGN KEY (DepartmentID) REFERENCES dbo.Departments(DepartmentID)
);
GO

CREATE TABLE dbo.Courses (
    CourseID INT IDENTITY(1,1) PRIMARY KEY,
    DepartmentID INT NOT NULL,
    CourseCode NVARCHAR(12) NOT NULL UNIQUE,
    Title NVARCHAR(200) NOT NULL,
    Credits INT NOT NULL CHECK (Credits BETWEEN 1 AND 6),
    CONSTRAINT FK_Courses_Department FOREIGN KEY (DepartmentID) REFERENCES dbo.Departments(DepartmentID)
);
GO

CREATE TABLE dbo.Students (
    StudentID INT IDENTITY(1,1) PRIMARY KEY,
    ProgramID INT NULL,
    FirstName NVARCHAR(60) NOT NULL,
    LastName NVARCHAR(60) NOT NULL,
    DOB DATE NULL,
    EnrollmentDate DATE NULL,
    Email NVARCHAR(150) NULL UNIQUE,
    CONSTRAINT FK_Students_Program FOREIGN KEY (ProgramID) REFERENCES dbo.Programs(ProgramID)
);
GO

CREATE TABLE dbo.Classes (
    ClassID INT IDENTITY(1,1) PRIMARY KEY,
    CourseID INT NOT NULL,
    TeacherID INT NOT NULL,
    RoomID INT NULL,
    Semester NVARCHAR(20) NOT NULL,
    Year INT NOT NULL CHECK (Year >= 2000),
    Schedule NVARCHAR(100) NULL,
    MaxCapacity INT NULL CHECK (MaxCapacity > 0),
    CONSTRAINT FK_Classes_Course FOREIGN KEY (CourseID) REFERENCES dbo.Courses(CourseID),
    CONSTRAINT FK_Classes_Teacher FOREIGN KEY (TeacherID) REFERENCES dbo.Teachers(TeacherID),
    CONSTRAINT FK_Classes_Room FOREIGN KEY (RoomID) REFERENCES dbo.Rooms(RoomID)
);
GO

CREATE TABLE dbo.Enrollments (
    StudentID INT NOT NULL,
    ClassID INT NOT NULL,
    EnrollmentDate DATE NOT NULL DEFAULT CONVERT(date, GETDATE()),
    Status NVARCHAR(20) NOT NULL DEFAULT 'enrolled',
    Grade DECIMAL(5,2) NULL,
    CONSTRAINT PK_Enrollments PRIMARY KEY (StudentID, ClassID),
    CONSTRAINT FK_Enrollments_Student FOREIGN KEY (StudentID) REFERENCES dbo.Students(StudentID),
    CONSTRAINT FK_Enrollments_Class FOREIGN KEY (ClassID) REFERENCES dbo.Classes(ClassID)
);
GO

CREATE TABLE dbo.Assignments (
    AssignmentID INT IDENTITY(1,1) PRIMARY KEY,
    ClassID INT NOT NULL,
    Title NVARCHAR(200) NOT NULL,
    Description NVARCHAR(MAX) NULL,
    DueDate DATE NULL,
    MaxPoints INT NOT NULL DEFAULT 100,
    CONSTRAINT FK_Assignments_Class FOREIGN KEY (ClassID) REFERENCES dbo.Classes(ClassID)
);
GO

CREATE TABLE dbo.Submissions (
    SubmissionID INT IDENTITY(1,1) PRIMARY KEY,
    AssignmentID INT NOT NULL,
    StudentID INT NOT NULL,
    SubmittedAt DATETIME2 NOT NULL DEFAULT SYSUTCDATETIME(),
    Score DECIMAL(6,2) NULL,
    Content NVARCHAR(MAX) NULL,
    CONSTRAINT FK_Submissions_Assignment FOREIGN KEY (AssignmentID) REFERENCES dbo.Assignments(AssignmentID),
    CONSTRAINT FK_Submissions_Student FOREIGN KEY (StudentID) REFERENCES dbo.Students(StudentID),
    CONSTRAINT UQ_Submission_Assignment_Student UNIQUE (AssignmentID, StudentID)
);
GO

INSERT INTO dbo.Departments (Name, Office) VALUES ('Computer Science','A101'), ('Mathematics','B201');
INSERT INTO dbo.Programs (DepartmentID, Name, DegreeType) VALUES (1,'BSc Computer Science','BSc'), (2,'BSc Mathematics','BSc');
INSERT INTO dbo.Rooms (Building,RoomNumber,Capacity) VALUES ('Main','101',40),('Main','102',30);
INSERT INTO dbo.Teachers (DepartmentID, FirstName, LastName, Email) VALUES (1,'Alice','Popescu','alice@school.local'), (2,'Bogdan','Ionescu','bogdan@school.local');
INSERT INTO dbo.Courses (DepartmentID, CourseCode, Title, Credits) VALUES (1,'CS101','Intro to Programming',5),(2,'MATH101','Calculus I',5);
INSERT INTO dbo.Students (ProgramID, FirstName, LastName, DOB, EnrollmentDate, Email) VALUES (1,'Ana','Georgescu','2004-05-12','2022-09-01','ana@example.com'), (1,'Mihai','Dumitru','2003-11-20','2021-09-01','mihai@example.com');
INSERT INTO dbo.Classes (CourseID, TeacherID, RoomID, Semester, Year, Schedule, MaxCapacity) VALUES (1,1,1,'Fall',2024,'Mon/Wed 10:00-11:30',40),(2,2,2,'Fall',2024,'Tue/Thu 09:00-10:30',30);
INSERT INTO dbo.Enrollments (StudentID, ClassID) VALUES (1,1),(2,1),(2,2);
INSERT INTO dbo.Assignments (ClassID, Title, DueDate) VALUES (1,'HW1 - Variables','2024-09-15'),(1,'HW2 - Loops','2024-10-01');
INSERT INTO dbo.Submissions (AssignmentID, StudentID, SubmittedAt, Score, Content) VALUES (1,1,'2024-09-14 18:00',95,'hw1.zip');
GO



