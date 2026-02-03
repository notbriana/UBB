USE SchoolDB;
GO


SELECT *
FROM dbo.Departments;
GO

SELECT *
FROM dbo.Departments
WHERE DepartmentID = 1;
GO


CREATE NONCLUSTERED INDEX IX_Departments_Office
ON dbo.Departments(Office);
GO

SELECT Office
FROM dbo.Departments;
GO


SELECT Office
FROM dbo.Departments
WHERE Office = 'A101';
GO

SELECT DepartmentID, Office
FROM dbo.Departments
WHERE Office = 'A101';
GO


SELECT DepartmentID, Name, Office
FROM dbo.Departments
WHERE Office = 'A101';
GO


SET STATISTICS IO ON;
SET STATISTICS TIME ON;
GO

SELECT *
FROM dbo.Students
WHERE Email = 'ana@example.com';
GO


CREATE NONCLUSTERED INDEX IX_Students_Email
ON dbo.Students(Email);
GO


SELECT *
FROM dbo.Students
WHERE Email = 'ana@example.com';
GO

SET STATISTICS IO OFF;
SET STATISTICS TIME OFF;
GO


CREATE OR ALTER VIEW dbo.V_Student_Class_Enrollments
AS
SELECT
    s.StudentID,
    s.FirstName + ' ' + s.LastName AS StudentName,
    s.Email AS StudentEmail,
    c.CourseCode,
    co.Title AS CourseName,
    cl.Semester,
    cl.Year,
    t.FirstName + ' ' + t.LastName AS TeacherName,
    e.EnrollmentDate,
    e.Grade
FROM dbo.Enrollments e
JOIN dbo.Students s ON e.StudentID = s.StudentID
JOIN dbo.Classes cl ON e.ClassID = cl.ClassID
JOIN dbo.Courses c ON cl.CourseID = c.CourseID
JOIN dbo.Teachers t ON cl.TeacherID = t.TeacherID
LEFT JOIN dbo.Courses co ON c.CourseID = co.CourseID;
GO

SELECT * FROM dbo.V_Student_Class_Enrollments;
GO

CREATE NONCLUSTERED INDEX IX_Enrollments_StudentID
ON dbo.Enrollments(StudentID);
GO

CREATE NONCLUSTERED INDEX IX_Enrollments_ClassID
ON dbo.Enrollments(ClassID);
GO

CREATE NONCLUSTERED INDEX IX_Classes_CourseID
ON dbo.Classes(CourseID);
GO

CREATE NONCLUSTERED INDEX IX_Classes_TeacherID
ON dbo.Classes(TeacherID);
GO


SELECT * FROM dbo.V_Student_Class_Enrollments;
GO


SELECT * 
FROM dbo.V_Student_Class_Enrollments
WHERE StudentEmail = 'ana@example.com';
GO

CREATE OR ALTER VIEW dbo.V_Teacher_Workload
AS
SELECT
    t.TeacherID,
    t.FirstName + ' ' + t.LastName AS TeacherName,
    t.Email AS TeacherEmail,
    d.Name AS DepartmentName,
    COUNT(cl.ClassID) AS NumberOfClasses,
    STRING_AGG(c.CourseCode, ', ') AS Courses
FROM dbo.Teachers t
JOIN dbo.Departments d ON t.DepartmentID = d.DepartmentID
LEFT JOIN dbo.Classes cl ON t.TeacherID = cl.TeacherID
LEFT JOIN dbo.Courses c ON cl.CourseID = c.CourseID
GROUP BY 
    t.TeacherID,
    t.FirstName,
    t.LastName,
    t.Email,
    d.Name;
GO

SELECT * FROM dbo.V_Teacher_Workload;
GO

SELECT 
    OBJECT_NAME(i.object_id) AS TableName,
    i.name AS IndexName,
    i.type_desc AS IndexType,
    STRING_AGG(COL_NAME(ic.object_id, ic.column_id), ', ') 
        WITHIN GROUP (ORDER BY ic.key_ordinal) AS IndexColumns
FROM sys.indexes i
INNER JOIN sys.index_columns ic 
    ON i.object_id = ic.object_id 
    AND i.index_id = ic.index_id
WHERE OBJECT_NAME(i.object_id) IN ('Departments', 'Students', 'Enrollments', 'Classes', 'Courses', 'Teachers')
    AND i.type_desc <> 'HEAP'
GROUP BY 
    OBJECT_NAME(i.object_id),
    i.name,
    i.type_desc,
    i.index_id
ORDER BY TableName, i.index_id;
GO
