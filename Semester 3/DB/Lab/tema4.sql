use SchoolDB
go


-- drop all the foreign key constraints
if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunTables_Tables]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunTables] DROP CONSTRAINT FK_TestRunTables_Tables
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestTables_Tables]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestTables] DROP CONSTRAINT FK_TestTables_Tables
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunTables_TestRuns]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunTables] DROP CONSTRAINT FK_TestRunTables_TestRuns
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunViews_TestRuns]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunViews] DROP CONSTRAINT FK_TestRunViews_TestRuns
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestTables_Tests]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestTables] DROP CONSTRAINT FK_TestTables_Tests
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestViews_Tests]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestViews] DROP CONSTRAINT FK_TestViews_Tests
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunViews_Views]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunViews] DROP CONSTRAINT FK_TestRunViews_Views
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestViews_Views]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestViews] DROP CONSTRAINT FK_TestViews_Views
GO


-- drop tables
if exists (select * from dbo.sysobjects where id = object_id(N'[Tables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [Tables]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestRunTables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestRunTables]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestRunViews]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestRunViews]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestRuns]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestRuns]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestTables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestTables]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestViews]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestViews]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[Tests]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [Tests]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[Views]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [Views]
GO


-- create the tables
CREATE TABLE [Tables] (
	[TableID] [int] IDENTITY (1, 1) NOT NULL ,
	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL
) ON [PRIMARY]
GO


CREATE TABLE [TestRunTables] (
	[TestRunID] [int] NOT NULL ,
	[TableID] [int] NOT NULL ,
	[StartAt] [datetime] NOT NULL ,
	[EndAt] [datetime] NOT NULL
) ON [PRIMARY]
GO


CREATE TABLE [TestRunViews] (
	[TestRunID] [int] NOT NULL ,
	[ViewID] [int] NOT NULL ,
	[StartAt] [datetime] NOT NULL ,
	[EndAt] [datetime] NOT NULL
) ON [PRIMARY]
GO

CREATE TABLE [TestRuns] (
	[TestRunID] [int] IDENTITY (1, 1) NOT NULL ,
	[Description] [nvarchar] (2000) COLLATE SQL_Latin1_General_CP1_CI_AS NULL ,
	[StartAt] [datetime] NULL ,
	[EndAt] [datetime] NULL
) ON [PRIMARY]
GO


CREATE TABLE [TestTables] (
	[TestID] [int] NOT NULL ,
	[TableID] [int] NOT NULL ,
	[NoOfRows] [int] NOT NULL ,
	[Position] [int] NOT NULL
) ON [PRIMARY]
GO


CREATE TABLE [TestViews] (
	[TestID] [int] NOT NULL ,
	[ViewID] [int] NOT NULL
) ON [PRIMARY]
GO


CREATE TABLE [Tests] (
	[TestID] [int] IDENTITY (1, 1) NOT NULL ,
	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL
) ON [PRIMARY]
GO


CREATE TABLE [Views] (
	[ViewID] [int] IDENTITY (1, 1) NOT NULL ,
	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL
) ON [PRIMARY]
GO


-- adding the constraints
ALTER TABLE [Tables] WITH NOCHECK 
	ADD	CONSTRAINT [PK_Tables] PRIMARY KEY  CLUSTERED
	([TableID]) ON [PRIMARY]
GO


ALTER TABLE [TestRunTables] WITH NOCHECK 
	ADD	CONSTRAINT [PK_TestRunTables] PRIMARY KEY  CLUSTERED
	([TestRunID], [TableID]) ON [PRIMARY]
GO


ALTER TABLE [TestRunViews] WITH NOCHECK 
	ADD	CONSTRAINT [PK_TestRunViews] PRIMARY KEY  CLUSTERED
	([TestRunID], [ViewID]) ON [PRIMARY]
GO


ALTER TABLE [TestRuns] WITH NOCHECK 
	ADD	CONSTRAINT [PK_TestRuns] PRIMARY KEY  CLUSTERED
	([TestRunID]) ON [PRIMARY]
GO


ALTER TABLE [TestTables] WITH NOCHECK 
	ADD	CONSTRAINT [PK_TestTables] PRIMARY KEY  CLUSTERED
	([TestID], [TableID]) ON [PRIMARY]
GO


ALTER TABLE [TestViews] WITH NOCHECK 
	ADD	CONSTRAINT [PK_TestViews] PRIMARY KEY  CLUSTERED
	([TestID], [ViewID]) ON [PRIMARY]
GO


ALTER TABLE [Tests] WITH NOCHECK 
	ADD	CONSTRAINT [PK_Tests] PRIMARY KEY  CLUSTERED
	([TestID]) ON [PRIMARY]
GO


ALTER TABLE [Views] WITH NOCHECK 
	ADD CONSTRAINT [PK_Views] PRIMARY KEY  CLUSTERED
	([ViewID]) ON [PRIMARY]
GO


ALTER TABLE [TestRunTables] ADD
	CONSTRAINT [FK_TestRunTables_Tables] FOREIGN KEY
	([TableID]) REFERENCES [Tables] ([TableID]) ON DELETE CASCADE  ON UPDATE CASCADE,
	CONSTRAINT [FK_TestRunTables_TestRuns] FOREIGN KEY
	([TestRunID]) REFERENCES [TestRuns] ([TestRunID]) ON DELETE CASCADE  ON UPDATE CASCADE
GO


ALTER TABLE [TestRunViews] ADD
	CONSTRAINT [FK_TestRunViews_TestRuns] FOREIGN KEY
	([TestRunID]) REFERENCES [TestRuns] ([TestRunID]) ON DELETE CASCADE  ON UPDATE CASCADE,
	CONSTRAINT [FK_TestRunViews_Views] FOREIGN KEY
	([ViewID]) REFERENCES [Views] ([ViewID]) ON DELETE CASCADE  ON UPDATE CASCADE
GO


ALTER TABLE [TestTables] ADD
	CONSTRAINT [FK_TestTables_Tables] FOREIGN KEY
	([TableID]) REFERENCES [Tables] ([TableID]) ON DELETE CASCADE  ON UPDATE CASCADE,
	CONSTRAINT [FK_TestTables_Tests] FOREIGN KEY
	([TestID]) REFERENCES [Tests] ([TestID]) ON DELETE CASCADE  ON UPDATE CASCADE
GO


ALTER TABLE [TestViews] ADD
	CONSTRAINT [FK_TestViews_Tests] FOREIGN KEY
	([TestID]) REFERENCES [Tests] ([TestID]),
	CONSTRAINT [FK_TestViews_Views] FOREIGN KEY
	([ViewID]) REFERENCES [Views] ([ViewID])
GO



-- start the lab
drop procedure addToViews
drop procedure addToTests
drop procedure addToTables
drop procedure connectTableToTest
drop procedure connectViewToTest
drop procedure if exists runTest2
go

CREATE PROCEDURE addToTables
	(@tableName VARCHAR(255))
AS
IF @tableName NOT IN (SELECT TABLE_NAME
FROM INFORMATION_SCHEMA.TABLES) BEGIN
	PRINT 'Table doesn''t exist'
	RETURN
END
IF @tableName IN (SELECT Name
FROM Tables) BEGIN
	PRINT 'Table already in Tables'
	RETURN
END
INSERT INTO Tables
	(Name)
Values
	(@tableName);
go


CREATE PROCEDURE addToViews
	(@viewName VARCHAR(255))
AS
IF @viewName NOT IN (SELECT TABLE_NAME
FROM INFORMATION_SCHEMA.VIEWS) BEGIN
	PRINT 'View doesn''t exist'
	RETURN
END
IF @viewName IN (SELECT Name
FROM Views) BEGIN
	PRINT 'View already in views'
	RETURN
END
INSERT INTO Views
	(Name)
Values
	(@viewName);
go

CREATE PROCEDURE addToTests
	(@testName VARCHAR(255))
AS
IF @testName IN (SELECT Name
FROM Tests) BEGIN
	PRINT 'Test already in tests'
	RETURN
END
INSERT INTO Tests
	(Name)
Values
	(@testName);
go

CREATE PROCEDURE connectTableToTest
	(@tableName VARCHAR(255),
	@testName VARCHAR(255),
	@rows INT,
	@pos INT)
AS
IF @tableName NOT IN (SELECT Name
FROM Tables) BEGIN
	PRINT 'Table not in Tables'
	RETURN
END
IF @testName NOT IN (SELECT Name
FROM Tests) BEGIN
	PRINT 'Test not in tests'
	RETURN
END
DECLARE @tableId int
DECLARE @testId int
SET @tableId = (SELECT TableID
FROM Tables
WHERE Name=@tableName)
SET @testId = (SELECT TestID
FROM Tests
WHERE Name=@testName)
IF EXISTS(SELECT *
FROM TestTables
WHERE TestId=@testId AND TableId=@tableId) BEGIN
	PRINT 'TestTable connection already exists'
END

INSERT INTO TestTables
VALUES(@testId, @tableId, @rows, @pos);
go



CREATE PROCEDURE connectViewToTest(@viewName VARCHAR(255),
	@testName VARCHAR(255))
AS
IF @viewName NOT IN (SELECT Name
FROM Views) BEGIN
	PRINT 'Table not in Tables'
	RETURN
END
IF @testName NOT IN (SELECT Name
FROM Tests) BEGIN
	PRINT 'Test not in tests'
	RETURN
END
DECLARE @viewId int
DECLARE @testId int
SET @viewId = (SELECT ViewID
FROM Views
WHERE Name=@viewName)
SET @testId = (SELECT TestID
FROM Tests
WHERE Name=@testName)
IF EXISTS(SELECT *
FROM TestViews
WHERE TestId=@testId AND ViewID=@viewId) BEGIN
	PRINT 'TestView connection already exists'
END

INSERT INTO TestViews
VALUES(@testId, @viewId);
go


CREATE PROCEDURE runTest2(@testName VARCHAR(255),
	@description VARCHAR(255))
AS
IF @testName NOT IN (SELECT Name
FROM TESTS) BEGIN
	PRINT 'test not in Tests'
	RETURN
END


DECLARE @testStartTime DATETIME
DECLARE @testRunId INT
DECLARE @tableId INT
DECLARE @table VARCHAR(255)
DECLARE @rows INT
DECLARE @pos INT
DECLARE @command VARCHAR(255)
DECLARE @tableInsertStartTime DATETIME
DECLARE @tableInsertEndTime DATETIME
DECLARE @testId INT
DECLARE @view VARCHAR(255)
DECLARE @viewId INT
DECLARE @viewStartTime DATETIME
DECLARE @viewEndTime DATETIME

SET @testId = (SELECT TestId
FROM Tests T
WHERE T.Name = @testName)

DECLARE tableCursor CURSOR SCROLL FOR 
		SELECT T1.Name, T1.TableId, T2.NoOfRows, T2.Position
FROM Tables T1 INNER JOIN TestTables T2 ON T1.TableID = T2.TableID
WHERE T2.TestID = @testId
ORDER BY T2.Position ASC


DECLARE viewCursor CURSOR SCROLL FOR 
		SELECT V.Name, V.ViewId
FROM Views V INNER JOIN TestViews TV ON V.ViewID = TV.ViewID
WHERE TV.TestID = @testId


SET @testStartTime = sysdatetime()

INSERT INTO TestRuns
	(Description, StartAt, EndAt)
VALUES(@description, @testStartTime, @testStartTime)
SET @testRunId = SCOPE_IDENTITY()

OPEN tableCursor
FETCH FIRST FROM tableCursor INTO @table, @tableId, @rows, @pos

WHILE @@FETCH_STATUS = 0 BEGIN
	EXEC ('DELETE FROM ' + @table)
	FETCH tableCursor INTO @table, @tableId, @rows, @pos
END

FETCH LAST FROM tableCursor INTO @table, @tableId, @rows, @pos

WHILE @@FETCH_STATUS = 0 BEGIN
	SET @command = 'populateTable'
	SET @tableInsertStartTime = sysdatetime()
	IF @rows > 0 BEGIN
		EXEC (@command + @table + ' ' + @rows)
	END
	SET @tableInsertEndTime = sysdatetime()
	INSERT INTO TestRunTables
	VALUES(@testRunId, @tableId, @tableInsertStartTime, @tableInsertEndTime)
	FETCH PRIOR FROM tableCursor INTO @table, @tableId, @rows, @pos
END
CLOSE tableCursor
DEALLOCATE tableCursor

OPEN viewCursor
FETCH viewCursor INTO @view, @viewId

WHILE @@FETCH_STATUS = 0 BEGIN
	SET @viewStartTime = sysdatetime()
	EXEC ('SELECT * FROM ' + @view)
	SET @viewEndTime = sysdatetime()
	INSERT INTO TestRunViews
	VALUES(@testRunID, @viewId, @viewStartTime, @viewEndTime)
	FETCH viewCursor INTO @view, @viewId
END
CLOSE viewCursor
DEALLOCATE viewCursor
UPDATE TestRuns 
	SET EndAt = sysdatetime()
	WHERE TestRunID = @testRunId;
go



-- altceva
IF EXISTS(SELECT *
FROM INFORMATION_SCHEMA.ROUTINES
WHERE ROUTINE_NAME = 'dropExistingProcedure') BEGIN
	DROP PROCEDURE dropExistingProcedure
END
GO

IF EXISTS(SELECT *
FROM INFORMATION_SCHEMA.ROUTINES
WHERE ROUTINE_NAME = 'dropExistingView') BEGIN
	DROP PROCEDURE dropExistingView
END
GO

CREATE PROCEDURE dropExistingProcedure(@tableName VARCHAR(255))
AS
IF EXISTS (SELECT *
FROM INFORMATION_SCHEMA.ROUTINES
WHERE ROUTINE_NAME = @tableName) BEGIN
	EXEC ('DROP PROCEDURE ' + @tableName)
END
go

CREATE PROCEDURE dropExistingView(@viewName VARCHAR(255))
AS
IF EXISTS (SELECT *
FROM INFORMATION_SCHEMA.VIEWS
WHERE TABLE_NAME = @viewName) BEGIN
	EXEC ('DROP VIEW ' + @viewName)
END
go

-- 1 PK
CREATE PROCEDURE populateTableDepartments(@rows INT)
AS
DECLARE @i INT
SET @i = 0
WHILE @i < @rows BEGIN
	INSERT INTO Departments
		(Name, Office)
	VALUES('Department' + CAST(@i AS VARCHAR(255)), 'Office' + CAST(@i AS VARCHAR(255)))
	SET @i = @i + 1
END
GO

-- 1 PK and 1 FK 
CREATE PROCEDURE populateTableTeachers(@rows INT)
AS
DECLARE @i INT
SET @i = 0
DECLARE @deptId INT
SET @deptId = (SELECT TOP 1 DepartmentID FROM Departments)
WHILE @i < @rows BEGIN
	INSERT INTO Teachers
		(DepartmentID, FirstName, LastName, Email, HireDate, IsActive)
	VALUES(@deptId, 'FirstName' + CAST(@i AS VARCHAR(255)), 'LastName' + CAST(@i AS VARCHAR(255)), 
		   'teacher' + CAST(@i AS VARCHAR(255)) + '@school.local', GETDATE(), 1)
	SET @i = @i + 1
END
GO

-- Multicolumn PK
CREATE PROCEDURE populateTableEnrollments(@rows INT)
AS
DECLARE @i INT
SET @i = 0
DECLARE @studentId INT
DECLARE @classId INT
SET @studentId = (SELECT TOP 1 StudentID FROM Students)
SET @classId = (SELECT TOP 1 ClassID FROM Classes)
WHILE @i < @rows BEGIN
	INSERT INTO Enrollments
		(StudentID, ClassID, EnrollmentDate, Status, Grade)
	VALUES(@studentId, @classId + @i, GETDATE(), 'enrolled', 85.5)
	SET @i = @i + 1
END
GO


-- a view on one table
CREATE VIEW DepartmentsView
AS
	SELECT * FROM Departments
GO

-- a view with 2 tables
CREATE VIEW TeacherDepartmentView
AS 
	SELECT d.Name AS DepartmentName, t.FirstName, t.LastName, t.Email, t.HireDate
	FROM Departments d INNER JOIN Teachers t ON d.DepartmentID = t.DepartmentID
GO

--  a view with Group By
CREATE VIEW TeacherDepartmentGroupedView
AS
	SELECT d.Name AS DepartmentName, COUNT(*) AS TeacherCount
	FROM Departments d JOIN Teachers t ON d.DepartmentID = t.DepartmentID
	GROUP BY d.Name
GO


-- execution of the lab
EXEC addToTables 'Departments'
EXEC addToTables 'Teachers'
EXEC addToTables 'Enrollments'
EXEC addToViews 'DepartmentsView'
EXEC addToViews 'TeacherDepartmentView'
EXEC addToViews 'TeacherDepartmentGroupedView'

EXEC addToTests 'MainTest5'

EXEC connectTableToTest 'Departments', 'MainTest5', 1000, 1
EXEC connectTableToTest 'Teachers', 'MainTest5', 1000, 2
EXEC connectTableToTest 'Enrollments', 'MainTest5', 1000, 3

EXEC connectViewToTest 'DepartmentsView', 'MainTest5'
EXEC connectViewToTest 'TeacherDepartmentView', 'MainTest5'
EXEC connectViewToTest 'TeacherDepartmentGroupedView', 'MainTest5'

EXEC runTest2 'MainTest5', 'Test5 cu 1000 de randuri'
GO

select * from Tables
select * from Tests
select * from TestTables
select * from TestRuns
select * from TestRunTables
select * from TestRunViews

delete from Tables
delete from Tests
delete from TestTables
delete from TestRuns
delete from TestTables
delete from TestViews
delete from TestRunTables
delete from TestRunViews