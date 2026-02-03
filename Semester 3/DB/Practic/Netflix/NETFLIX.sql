-- Create database
CREATE DATABASE NetflixDB;
GO

USE NetflixDB;
GO

-- Accounts
CREATE TABLE Accounts (
    account_id INT IDENTITY(1,1) PRIMARY KEY,
    email VARCHAR(100) NOT NULL UNIQUE,
    join_date DATE NOT NULL,
    is_active BIT NOT NULL
);

-- Actors
CREATE TABLE Actors (
    actor_id INT IDENTITY(1,1) PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    nationality VARCHAR(50)
);

-- Movies
CREATE TABLE Movies (
    movie_id INT IDENTITY(1,1) PRIMARY KEY,
    title VARCHAR(150) NOT NULL,
    duration INT NOT NULL CHECK (duration >= 0)
);

-- Many-to-many relationship: Movies ↔ Actors
CREATE TABLE MovieActor (
    movie_id INT NOT NULL,
    actor_id INT NOT NULL,
    PRIMARY KEY (movie_id, actor_id),
    FOREIGN KEY (movie_id) REFERENCES Movies(movie_id),
    FOREIGN KEY (actor_id) REFERENCES Actors(actor_id)
);

-- Reviews: Accounts review Movies
CREATE TABLE Reviews (
    review_id INT IDENTITY(1,1) PRIMARY KEY,
    account_id INT NOT NULL,
    movie_id INT NOT NULL,
    review_date DATE NOT NULL,
    rating FLOAT CHECK (rating >= 0 AND rating <= 10),
    review_text VARCHAR(MAX),
    FOREIGN KEY (account_id) REFERENCES Accounts(account_id),
    FOREIGN KEY (movie_id) REFERENCES Movies(movie_id)
);

-- Watchlists: movies watched by accounts
CREATE TABLE Watchlists (
    account_id INT NOT NULL,
    movie_id INT NOT NULL,
    watched_date DATE NOT NULL,
    PRIMARY KEY (account_id, movie_id),
    FOREIGN KEY (account_id) REFERENCES Accounts(account_id),
    FOREIGN KEY (movie_id) REFERENCES Movies(movie_id)
);
GO
