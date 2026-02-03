CREATE DATABASE FlightOperationsDB;
GO

CREATE TABLE Airlines(
	airline_id INT IDENTITY(1,1) PRIMARY KEY,
	name VARCHAR(100) NOT NULL,
	description VARCHAR(255)
);

CREATE TABLE Airports(
	airport_id INT IDENTITY(1,1) PRIMARY KEY,
	name VARCHAR(100) NOT NULL UNIQUE,
	location VARCHAR(100) NOT NULL
);

CREATE TABLE Airplanes(
	airplane_id INT IDENTITY(1,1) PRIMARY KEY,
	name VARCHAR(100) NOT NULL,
	airline_id INT NOT NULL,
	FOREIGN KEY (airline_id) REFERENCES Airlines(airline_id)
);

CREATE TABLE Flights(
	flight_id INT IDENTITY(1,1) PRIMARY KEY,
	departure_time DATETIME NOT NULL,
	duration INT NOT NULL,
	ticket_price DECIMAL(10,2) NOT NULL,
    departure_airport_id INT NOT NULL,
    destination_airport_id INT NOT NULL,
	airplane_id INT NOT NULL,
	FOREIGN KEY (departure_airport_id) REFERENCES Airports(airport_id),
    FOREIGN KEY (destination_airport_id) REFERENCES Airports(airport_id),
    FOREIGN KEY (airplane_id) REFERENCES Airplanes(airplane_id)
)

CREATE TABLE Pilots (
    pilot_id INT IDENTITY PRIMARY KEY,
    name VARCHAR(100) NOT NULL
);

CREATE TABLE Reviews (
    pilot_id INT NOT NULL,
    flight_id INT NOT NULL,
    review_text VARCHAR(255),
    stars INT CHECK (stars BETWEEN 1 AND 5),
    PRIMARY KEY (pilot_id, flight_id),
    FOREIGN KEY (pilot_id) REFERENCES Pilots(pilot_id),
    FOREIGN KEY (flight_id) REFERENCES Flights(flight_id)
);

