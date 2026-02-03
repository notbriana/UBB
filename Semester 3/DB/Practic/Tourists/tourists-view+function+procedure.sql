CREATE DATABASE MuseumDB

CREATE TABLE Museums(
	museum_id INT IDENTITY(1,1) PRIMARY KEY,
	name VARCHAR(100) NOT NULL,
	opening_year INT NOT NULL,
	city VARCHAR(100) NOT NULL,
	country VARCHAR(100) NOT NULL
)

CREATE TABLE Exhibitions(
	exhibition_id INT IDENTITY(1,1) PRIMARY KEY,
	name VARCHAR(100) NOT NULL,
	description VARCHAR(100),
	museum_id INT NOT NULL,
	FOREIGN KEY (museum_id) REFERENCES Museums(museum_id)
)

CREATE TABLE Tours (
    tour_id INT IDENTITY(1,1) PRIMARY KEY,
    name VARCHAR(150) NOT NULL,
    tour_date DATETIME NOT NULL,
    guide_name VARCHAR(100) NOT NULL,
    ticket_price DECIMAL(10,2) NOT NULL,
    museum_id INT NOT NULL,
    FOREIGN KEY (museum_id) REFERENCES Museums(museum_id)
);

CREATE TABLE Tourists (
    tourist_id INT IDENTITY(1,1) PRIMARY KEY,
    first_name VARCHAR(100) NOT NULL,
    last_name VARCHAR(100) NOT NULL,
    gender CHAR(1),
    age INT
);


CREATE TABLE TouristTour (
    tour_id INT NOT NULL,
    tourist_id INT NOT NULL,
    tickets_bought INT NOT NULL,
    rate_given INT CHECK(rate_given >= 0 AND rate_given <= 10),
    PRIMARY KEY (tour_id, tourist_id),
    FOREIGN KEY (tour_id) REFERENCES Tours(tour_id),
    FOREIGN KEY (tourist_id) REFERENCES Tourists(tourist_id)
);

CREATE OR ALTER PROCEDURE AddTouristToTour
    @tour_id INT,
    @tourist_id INT,
    @tickets_bought INT,
    @rate_given INT
AS
BEGIN
    IF EXISTS (
        SELECT 1 
        FROM TouristTour 
        WHERE tour_id = @tour_id AND tourist_id = @tourist_id
    )
    BEGIN
        -- Update existing record
        UPDATE TouristTour
        SET tickets_bought = @tickets_bought,
            rate_given = @rate_given
        WHERE tour_id = @tour_id AND tourist_id = @tourist_id;
    END
    ELSE
    BEGIN
        -- Insert new record
        INSERT INTO TouristTour (tour_id, tourist_id, tickets_bought, rate_given)
        VALUES (@tour_id, @tourist_id, @tickets_bought, @rate_given);
    END
END;
GO


CREATE OR ALTER VIEW Exhibitions_NationalMuseum AS
SELECT e.name AS exhibition_name
FROM Exhibitions e
INNER JOIN Museums m ON e.museum_id = m.museum_id
WHERE m.name = 'National Museum of Art and Science';
GO


CREATE OR ALTER FUNCTION TouristsWithMinTours(@m INT)
RETURNS TABLE
AS
RETURN
(
    SELECT t.first_name, t.last_name, COUNT(tt.tour_id) AS tours_booked
    FROM Tourists t
    INNER JOIN TouristTour tt ON t.tourist_id = tt.tourist_id
    GROUP BY t.tourist_id, t.first_name, t.last_name
    HAVING COUNT(tt.tour_id) >= @m
);
GO


