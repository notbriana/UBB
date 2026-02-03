USE HealthDB;
GO


CREATE PROCEDURE AddHealthMetric
	@user_id INT,
	@record_date DATE,
	@weight DECIMAL(5,2),
	@blood_pressure INT,
	@heart_rate INT
AS
BEGIN
	IF @record_date > CAST(GETDATE() AS DATE)
	BEGIN
		RAISERROR('ERROR: RECORD DATE CANT BE IN THE FUTURE', 16, 1);
		RETURN;
	END

	INSERT INTO HealthMetrics
	VALUES (@user_id, @record_date, @weight, @blood_pressure, @heart_rate);
END;


INSERT INTO Users (name, age, gender)
VALUES ('Alice', 25, 'Female');

EXEC AddHealthMetric
    @user_id = 1,
    @record_date = '2023-12-01',
    @weight = 65.50,
    @blood_pressure = 120,
    @heart_rate = 72;

SELECT * FROM HealthMetrics;

