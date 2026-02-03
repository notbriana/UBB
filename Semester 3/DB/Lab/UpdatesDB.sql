UPDATE dbo.Students
SET Email = Email + '.updated'
WHERE EnrollmentDate BETWEEN '2021-01-01' AND '2023-12-31'
AND Email IS NOT NULL;
GO

UPDATE dbo.Courses
SET Credits = Credits + 1
WHERE (Credits = 4 OR Credits = 5) 
AND DepartmentID IN (1,3);
GO

UPDATE dbo.Classes
SET MaxCapacity = MaxCapacity + 5
WHERE RoomID IS NOT NULL
OR Year < 2025;
GO
