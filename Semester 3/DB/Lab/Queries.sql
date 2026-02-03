USE SchoolDB;
GO

-- a)
SELECT FirstName, LastName, YEAR(GETDATE()) - YEAR(DOB) AS Age
FROM dbo.Students
WHERE ProgramID = 1
UNION ALL
SELECT FirstName, LastName, YEAR(GETDATE()) - YEAR(DOB) AS Age
FROM dbo.Students
WHERE ProgramID = 2;

SELECT DISTINCT CourseCode, Title, Credits * 2 AS DoubleCredits
FROM dbo.Courses
WHERE Credits >= 5 OR DepartmentID = 1
ORDER BY DoubleCredits DESC;


-- b) 

UPDATE dbo.Enrollments
SET Grade = 75
WHERE StudentID = 4;

UPDATE dbo.Enrollments
SET Grade = 80
WHERE StudentID = 2;

UPDATE dbo.Enrollments
SET Grade = 45
WHERE StudentID = 1;

UPDATE dbo.Enrollments
SET Grade = 60
WHERE StudentID = 3;


SELECT StudentID FROM dbo.Enrollments
WHERE ClassID IN (1, 2)
INTERSECT
SELECT StudentID FROM dbo.Enrollments
WHERE Grade >= 50;

SELECT DISTINCT FirstName, LastName
FROM dbo.Students
WHERE StudentID IN (
    SELECT StudentID FROM dbo.Enrollments
    WHERE ClassID = 1 OR ClassID = 2
) AND ProgramID = 1;


-- c) 
SELECT CourseID, Title FROM dbo.Courses
EXCEPT
SELECT CourseID, Title FROM dbo.Courses
WHERE DepartmentID = 2;

SELECT StudentID, FirstName
FROM dbo.Students
WHERE StudentID NOT IN (
    SELECT StudentID FROM dbo.Enrollments WHERE ClassID = 1
) AND EnrollmentDate IS NOT NULL;

-- d)

SELECT s.FirstName, s.LastName, c.Title, (c.Credits * 2) AS DoubleCredits
FROM dbo.Students s
INNER JOIN dbo.Enrollments e ON s.StudentID = e.StudentID
INNER JOIN dbo.Classes cl ON e.ClassID = cl.ClassID
INNER JOIN dbo.Courses c ON cl.CourseID = c.CourseID
WHERE (s.ProgramID = 1 OR s.ProgramID = 2)
ORDER BY DoubleCredits DESC;

SELECT DISTINCT s.FirstName, s.LastName, (YEAR(GETDATE()) - YEAR(s.DOB)) AS Age
FROM dbo.Students s
LEFT JOIN dbo.Enrollments e ON s.StudentID = e.StudentID
WHERE e.ClassID IS NOT NULL
ORDER BY Age DESC;

SELECT t.FirstName, t.LastName, c.Title, tc.Role
FROM dbo.TeacherCourses tc
RIGHT JOIN dbo.Teachers t ON tc.TeacherID = t.TeacherID
RIGHT JOIN dbo.Courses c ON tc.CourseID = c.CourseID
WHERE (tc.Role = 'Main' OR tc.Role IS NULL);

SELECT TOP 7 s.FirstName AS StudentFirstName, t.FirstName AS TeacherFirstName, c.Title, (c.Credits * 1.5) AS WeightedCredits
FROM dbo.Students s
FULL JOIN dbo.Enrollments e ON s.StudentID = e.StudentID
FULL JOIN dbo.Classes cl ON e.ClassID = cl.ClassID
FULL JOIN dbo.Courses c ON cl.CourseID = c.CourseID
FULL JOIN dbo.TeacherCourses tc ON c.CourseID = tc.CourseID
FULL JOIN dbo.Teachers t ON tc.TeacherID = t.TeacherID
WHERE (s.StudentID IS NOT NULL OR t.TeacherID IS NOT NULL)
ORDER BY WeightedCredits DESC;

-- e)

SELECT DISTINCT FirstName, LastName
FROM dbo.Students
WHERE StudentID IN (
    SELECT StudentID
    FROM dbo.Enrollments
    WHERE ClassID IN (
        SELECT ClassID
        FROM dbo.Classes
        WHERE Year = 2024
    )
)
ORDER BY LastName;


SELECT TOP 2 FirstName, LastName
FROM dbo.Students
WHERE ProgramID IN (
    SELECT ProgramID FROM dbo.Programs WHERE DegreeType = 'BSc' 
)


-- f)

SELECT DISTINCT s.FirstName, s.LastName
FROM dbo.Students s
WHERE EXISTS (
    SELECT 1
    FROM dbo.Submissions sub
    WHERE sub.StudentID = s.StudentID
      AND sub.Score > 90
);


SELECT s.FirstName, s.LastName
FROM dbo.Students s
WHERE EXISTS (
    SELECT 1
    FROM dbo.Enrollments e
    WHERE e.StudentID = s.StudentID
      AND e.ClassID IN (
          SELECT cl.ClassID
          FROM dbo.Classes cl
          WHERE cl.Year = 2025
      )
);

-- g)

SELECT AssignmentID, AvgScore
FROM (
    SELECT AssignmentID, AVG(Score) AS AvgScore
    FROM dbo.Submissions
    GROUP BY AssignmentID
) AS subquery
WHERE AvgScore > 80;

SELECT StudentID, EnrollmentCount
FROM (
    SELECT StudentID, COUNT(*) AS EnrollmentCount
    FROM dbo.Enrollments
    GROUP BY StudentID
) AS subquery
WHERE EnrollmentCount > 1;

-- h)

SELECT ProgramID, COUNT(*) AS StudentCount
FROM dbo.Students
GROUP BY ProgramID;

SELECT StudentID, SUM(Score) AS TotalScore
FROM dbo.Submissions
GROUP BY StudentID
HAVING SUM(Score) > (
    SELECT AVG(Score)
    FROM dbo.Submissions
    WHERE AssignmentID IN (
        SELECT AssignmentID
        FROM dbo.Assignments
        WHERE ClassID = 2
    )
);

SELECT AssignmentID, MAX(Score) AS MaxScore
FROM dbo.Submissions
GROUP BY AssignmentID
HAVING MAX(Score) > 90;

SELECT TeacherID, COUNT(CourseID) AS CourseCount
FROM dbo.TeacherCourses
GROUP BY TeacherID
HAVING COUNT(CourseID) > (
    SELECT AVG(CoursePerTeacher)
    FROM (
        SELECT COUNT(CourseID) AS CoursePerTeacher
        FROM dbo.TeacherCourses
        GROUP BY TeacherID
    ) AS Sub
);

-- i)

SELECT StudentID, Score
FROM dbo.Submissions
WHERE Score > ANY (
    SELECT Score
    FROM dbo.Submissions
    WHERE AssignmentID = 1
);


SELECT StudentID, Score
FROM dbo.Submissions
WHERE Score > ALL (
    SELECT Score
    FROM dbo.Submissions
    WHERE AssignmentID = 2
);


SELECT StudentID, Score
FROM dbo.Submissions
WHERE Score > ANY (
    SELECT Score
    FROM dbo.Submissions
    WHERE AssignmentID = 3
);


SELECT StudentID, Score
FROM dbo.Submissions
WHERE Score > ALL (
    SELECT Score
    FROM dbo.Submissions
    WHERE AssignmentID = 4
);

SELECT StudentID
FROM dbo.Students
WHERE StudentID NOT IN (SELECT StudentID FROM dbo.Submissions WHERE AssignmentID = 1);

SELECT StudentID
FROM dbo.Students
WHERE StudentID NOT IN (SELECT StudentID FROM dbo.Submissions WHERE AssignmentID = 3);

SELECT StudentID, SUM(Score) AS TotalScore
FROM dbo.Submissions
GROUP BY StudentID
HAVING SUM(Score) > 180;

SELECT StudentID, MAX(Score) AS MaxScore
FROM dbo.Submissions
GROUP BY StudentID
HAVING MAX(Score) < 95;



