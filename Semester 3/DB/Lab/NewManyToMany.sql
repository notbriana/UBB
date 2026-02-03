USE SchoolDB;
GO

CREATE TABLE dbo.TeacherCourses (
    TeacherID INT NOT NULL,
    CourseID INT NOT NULL,
    Role NVARCHAR(50) NULL,  -- optional: main teacher, assistant, etc.
    CONSTRAINT PK_TeacherCourses PRIMARY KEY (TeacherID, CourseID),
    CONSTRAINT FK_TeacherCourses_Teacher FOREIGN KEY (TeacherID) REFERENCES dbo.Teachers(TeacherID),
    CONSTRAINT FK_TeacherCourses_Course FOREIGN KEY (CourseID) REFERENCES dbo.Courses(CourseID)
);
GO
