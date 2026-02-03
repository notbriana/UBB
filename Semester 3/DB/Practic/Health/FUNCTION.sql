CREATE FUNCTION AvgActivityDuration (
    @user_id INT,
    @activity_id INT
)
RETURNS DECIMAL(6,2)
AS
BEGIN
    DECLARE @avg_duration DECIMAL(6,2);

    SELECT @avg_duration = AVG(duration_minutes)
    FROM UserActivitiesJournal
    WHERE user_id = @user_id
      AND activity_id = @activity_id;

    RETURN @avg_duration;
END;

