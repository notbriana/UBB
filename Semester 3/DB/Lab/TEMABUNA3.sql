USE SchoolDB
GO

IF OBJECT_ID('dbo.DatabaseVersion', 'U') IS NOT NULL
    DROP TABLE dbo.DatabaseVersion;
GO

CREATE TABLE dbo.DatabaseVersion (
    VersionID INT PRIMARY KEY,
    Description NVARCHAR(500),
    AppliedDate DATETIME2 DEFAULT SYSUTCDATETIME()
);
GO

INSERT INTO dbo.DatabaseVersion (VersionID, Description) VALUES (0, 'Initial database state');
GO


CREATE OR ALTER PROCEDURE dbo.Version1_Up
AS
BEGIN
    ALTER TABLE dbo.Students
    ALTER COLUMN Email NVARCHAR(200) NULL;
    
    PRINT 'Version 1 UP: Modified Students.Email to NVARCHAR(200)';
END
GO

CREATE OR ALTER PROCEDURE dbo.Version1_Down
AS
BEGIN
    ALTER TABLE dbo.Students
    ALTER COLUMN Email NVARCHAR(150) NULL;
    
    PRINT 'Version 1 DOWN: Reverted Students.Email to NVARCHAR(150)';
END
GO

CREATE OR ALTER PROCEDURE dbo.Version2_Up
AS
BEGIN
    ALTER TABLE dbo.Students
    ADD Phone NVARCHAR(20) NULL;
    
    PRINT 'Version 2 UP: Added Phone column to Students';
END
GO

CREATE OR ALTER PROCEDURE dbo.Version2_Down
AS
BEGIN
    ALTER TABLE dbo.Students
    DROP COLUMN Phone;
    
    PRINT 'Version 2 DOWN: Removed Phone column from Students';
END
GO

CREATE OR ALTER PROCEDURE dbo.Version3_Up
AS
BEGIN
    ALTER TABLE dbo.Students
    ADD CONSTRAINT DF_Students_EnrollmentDate DEFAULT GETDATE() FOR EnrollmentDate;
    
    PRINT 'Version 3 UP: Added DEFAULT constraint to Students.EnrollmentDate';
END
GO

CREATE OR ALTER PROCEDURE dbo.Version3_Down
AS
BEGIN
    ALTER TABLE dbo.Students
    DROP CONSTRAINT DF_Students_EnrollmentDate;
    
    PRINT 'Version 3 DOWN: Removed DEFAULT constraint from Students.EnrollmentDate';
END
GO

CREATE OR ALTER PROCEDURE dbo.Version4_Up
AS
BEGIN
    CREATE TABLE dbo.StudentContacts (
        StudentID INT NOT NULL,
        ContactType NVARCHAR(20) NOT NULL,
        ContactValue NVARCHAR(100) NOT NULL,
        CONSTRAINT PK_StudentContacts PRIMARY KEY (StudentID, ContactType)
    );
    
    PRINT 'Version 4 UP: Created StudentContacts table with composite primary key';
END
GO

CREATE OR ALTER PROCEDURE dbo.Version4_Down
AS
BEGIN
    IF OBJECT_ID('dbo.StudentContacts', 'U') IS NOT NULL
        DROP TABLE dbo.StudentContacts;
    
    PRINT 'Version 4 DOWN: Dropped StudentContacts table';
END
GO

CREATE OR ALTER PROCEDURE dbo.Version5_Up
AS
BEGIN
    IF NOT EXISTS (SELECT 1 FROM sys.indexes WHERE name = 'UQ_Teachers_Email_Extra' AND object_id = OBJECT_ID('dbo.Teachers'))
    BEGIN
        ALTER TABLE dbo.Teachers
        ADD CONSTRAINT UQ_Teachers_Email_Extra UNIQUE (Email);
        
        PRINT 'Version 5 UP: Added candidate key (UNIQUE) constraint to Teachers.Email';
    END
    ELSE
        PRINT 'Version 5 UP: Constraint already exists';
END
GO

CREATE OR ALTER PROCEDURE dbo.Version5_Down
AS
BEGIN
    IF EXISTS (SELECT 1 FROM sys.objects WHERE name = 'UQ_Teachers_Email_Extra' AND type = 'UQ')
    BEGIN
        ALTER TABLE dbo.Teachers
        DROP CONSTRAINT UQ_Teachers_Email_Extra;
        
        PRINT 'Version 5 DOWN: Removed candidate key constraint from Teachers.Email';
    END
    ELSE
        PRINT 'Version 5 DOWN: Constraint does not exist';
END
GO

CREATE OR ALTER PROCEDURE dbo.Version6_Up
AS
BEGIN
    IF OBJECT_ID('dbo.StudentContacts', 'U') IS NOT NULL
    BEGIN
        ALTER TABLE dbo.StudentContacts
        ADD CONSTRAINT FK_StudentContacts_Student 
        FOREIGN KEY (StudentID) REFERENCES dbo.Students(StudentID);
        
        PRINT 'Version 6 UP: Added foreign key from StudentContacts to Students';
    END
    ELSE
        PRINT 'Version 6 UP: StudentContacts table does not exist';
END
GO

CREATE OR ALTER PROCEDURE dbo.Version6_Down
AS
BEGIN
    IF EXISTS (SELECT 1 FROM sys.foreign_keys WHERE name = 'FK_StudentContacts_Student')
    BEGIN
        ALTER TABLE dbo.StudentContacts
        DROP CONSTRAINT FK_StudentContacts_Student;
        
        PRINT 'Version 6 DOWN: Removed foreign key from StudentContacts';
    END
    ELSE
        PRINT 'Version 6 DOWN: Foreign key does not exist';
END
GO


CREATE OR ALTER PROCEDURE dbo.Version7_Up
AS
BEGIN
    CREATE TABLE dbo.CoursePrerequisites (
        CourseID INT NOT NULL,
        PrerequisiteCourseID INT NOT NULL,
        CONSTRAINT PK_CoursePrerequisites PRIMARY KEY (CourseID, PrerequisiteCourseID),
        CONSTRAINT FK_CoursePrereq_Course FOREIGN KEY (CourseID) REFERENCES dbo.Courses(CourseID),
        CONSTRAINT FK_CoursePrereq_Prerequisite FOREIGN KEY (PrerequisiteCourseID) REFERENCES dbo.Courses(CourseID)
    );
    
    PRINT 'Version 7 UP: Created CoursePrerequisites table';
END
GO

CREATE OR ALTER PROCEDURE dbo.Version7_Down
AS
BEGIN
    IF OBJECT_ID('dbo.CoursePrerequisites', 'U') IS NOT NULL
        DROP TABLE dbo.CoursePrerequisites;
    
    PRINT 'Version 7 DOWN: Dropped CoursePrerequisites table';
END
GO

CREATE OR ALTER PROCEDURE dbo.GoToVersion
    @TargetVersion INT
AS
BEGIN
    SET NOCOUNT ON;
    
    DECLARE @CurrentVersion INT;
    DECLARE @StepVersion INT;
    
    SELECT @CurrentVersion = MAX(VersionID) FROM dbo.DatabaseVersion;
    
    IF @TargetVersion < 0 OR @TargetVersion > 7
    BEGIN
        RAISERROR('Invalid version number. Valid versions are 0-7.', 16, 1);
        RETURN;
    END
    
    IF @CurrentVersion = @TargetVersion
    BEGIN
        PRINT 'Already at version ' + CAST(@TargetVersion AS NVARCHAR(10));
        RETURN;
    END
    
    PRINT '========================================';
    PRINT 'Current version: ' + CAST(@CurrentVersion AS NVARCHAR(10));
    PRINT 'Target version: ' + CAST(@TargetVersion AS NVARCHAR(10));
    PRINT '========================================';
    
    IF @TargetVersion > @CurrentVersion
    BEGIN
        SET @StepVersion = @CurrentVersion + 1;
        
        WHILE @StepVersion <= @TargetVersion
        BEGIN
            PRINT '';
            PRINT 'Upgrading to version ' + CAST(@StepVersion AS NVARCHAR(10)) + '...';
            
            IF @StepVersion = 1
                EXEC dbo.Version1_Up;
            ELSE IF @StepVersion = 2
                EXEC dbo.Version2_Up;
            ELSE IF @StepVersion = 3
                EXEC dbo.Version3_Up;
            ELSE IF @StepVersion = 4
                EXEC dbo.Version4_Up;
            ELSE IF @StepVersion = 5
                EXEC dbo.Version5_Up;
            ELSE IF @StepVersion = 6
                EXEC dbo.Version6_Up;
            ELSE IF @StepVersion = 7
                EXEC dbo.Version7_Up;
            
            IF NOT EXISTS (SELECT 1 FROM dbo.DatabaseVersion WHERE VersionID = @StepVersion)
                INSERT INTO dbo.DatabaseVersion (VersionID, Description)
                VALUES (@StepVersion, 'Upgraded to version ' + CAST(@StepVersion AS NVARCHAR(10)));
            ELSE
                UPDATE dbo.DatabaseVersion 
                SET AppliedDate = SYSUTCDATETIME()
                WHERE VersionID = @StepVersion;
            
            SET @StepVersion = @StepVersion + 1;
        END
    END
    ELSE
    BEGIN
        SET @StepVersion = @CurrentVersion;
        
        WHILE @StepVersion > @TargetVersion
        BEGIN
            PRINT '';
            PRINT 'Downgrading from version ' + CAST(@StepVersion AS NVARCHAR(10)) + '...';
            
            IF @StepVersion = 1
                EXEC dbo.Version1_Down;
            ELSE IF @StepVersion = 2
                EXEC dbo.Version2_Down;
            ELSE IF @StepVersion = 3
                EXEC dbo.Version3_Down;
            ELSE IF @StepVersion = 4
                EXEC dbo.Version4_Down;
            ELSE IF @StepVersion = 5
                EXEC dbo.Version5_Down;
            ELSE IF @StepVersion = 6
                EXEC dbo.Version6_Down;
            ELSE IF @StepVersion = 7
                EXEC dbo.Version7_Down;
            
            DELETE FROM dbo.DatabaseVersion WHERE VersionID = @StepVersion;
            
            SET @StepVersion = @StepVersion - 1;
        END
    END
    
    PRINT '';
    PRINT '========================================';
    PRINT 'Successfully switched to version ' + CAST(@TargetVersion AS NVARCHAR(10));
    PRINT '========================================';
END
GO

CREATE OR ALTER PROCEDURE dbo.GetCurrentVersion
AS
BEGIN
    SELECT 
        MAX(VersionID) AS CurrentVersion,
        Description,
        AppliedDate
    FROM dbo.DatabaseVersion
    WHERE VersionID = (SELECT MAX(VersionID) FROM dbo.DatabaseVersion)
    GROUP BY Description, AppliedDate;
END
GO

EXEC GoToVersion 5;
SELECT * FROM dbo.DatabaseVersion;
