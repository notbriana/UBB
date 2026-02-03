CREATE OR ALTER PROCEDURE AddPilotReview
    @pilot_id INT,
    @flight_id INT,
    @review_text VARCHAR(255),
    @stars INT
AS
BEGIN
    IF EXISTS (
        SELECT 1
        FROM Reviews
        WHERE pilot_id = @pilot_id
          AND flight_id = @flight_id
    )
    BEGIN
        UPDATE Reviews
        SET review_text = @review_text,
            stars = @stars
        WHERE pilot_id = @pilot_id
          AND flight_id = @flight_id;
    END
    ELSE
    BEGIN
        INSERT INTO Reviews (pilot_id, flight_id, review_text, stars)
        VALUES (@pilot_id, @flight_id, @review_text, @stars);
    END
END;
GO


CREATE OR ALTER VIEW AirplanesWithMostFlights
AS
SELECT a.name
FROM Airplanes a
JOIN Flights f ON a.airplane_id = f.airplane_id
GROUP BY a.airplane_id, a.name
HAVING COUNT(*) = (
    SELECT MAX(flight_count)
    FROM (
        SELECT COUNT(*) AS flight_count
        FROM Flights
        GROUP BY airplane_id
    ) t
);
GO

CREATE OR ALTER FUNCTION FlightsFromXtoY
(
    @X VARCHAR(100),
    @Y VARCHAR(100)
)
RETURNS INT
AS
BEGIN
    DECLARE @cnt INT;

    SELECT @cnt = COUNT(*)
    FROM Flights f
    JOIN Airports a1 ON f.departure_airport_id = a1.airport_id
    JOIN Airports a2 ON f.destination_airport_id = a2.airport_id
    WHERE a1.name = @X
      AND a2.name = @Y;

    RETURN @cnt;
END;
GO


