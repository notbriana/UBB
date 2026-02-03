USE SchoolDB;
GO

DELETE FROM dbo.Submissions
WHERE Score < 90 OR Content IS NULL;
GO

DELETE FROM dbo.Rooms
WHERE RoomID NOT IN (SELECT DISTINCT RoomID FROM dbo.Classes WHERE RoomID IS NOT NULL);
GO
