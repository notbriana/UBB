CREATE DATABASE HealthDB;
GO

USE HealthDB;
GO

CREATE TABLE Users(
	user_id INT IDENTITY (1,1) PRIMARY KEY,
	name VARCHAR(100) NOT NULL UNIQUE,
	age INT NOT NULL,
	gender VARCHAR(10) NOT NULL
);

CREATE TABLE Activities(
	activity_id INT IDENTITY(1,1) PRIMARY KEY,
	name VARCHAR(100) NOT NULL UNIQUE,
	calories_burned_per_hour INT NOT NULL
);

CREATE TABLE Meals(
	meal_id INT IDENTITY(1,1) PRIMARY KEY,
	name VARCHAR(100) NOT NULL UNIQUE,
	calories_per_serving INT NOT NULL
);

CREATE TABLE HealthMetrics(
	metric_id INT IDENTITY(1,1) PRIMARY KEY,
	user_id INT NOT NULL,
	record_date DATE NOT NULL,
	weight DECIMAL(5,2) NOT NULL,
	blood_pressure INT NOT NULL,
	heart_rate INT NOT NULL,
	FOREIGN KEY (user_id) REFERENCES Users(user_id)
);

CREATE TABLE UserActivitiesJournal (
    journal_id INT IDENTITY(1,1) PRIMARY KEY,
    user_id INT NOT NULL,
    activity_id INT NOT NULL,
    activity_date DATE NOT NULL,
    duration_minutes INT NOT NULL,
    FOREIGN KEY (user_id) REFERENCES Users(user_id),
    FOREIGN KEY (activity_id) REFERENCES Activities(activity_id)
);

