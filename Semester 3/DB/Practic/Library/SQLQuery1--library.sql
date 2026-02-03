CREATE DATABASE LibraryBookDB;
GO


CREATE TABLE City (
    city_id INT IDENTITY(1,1) PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    county VARCHAR(100) NOT NULL,
    country VARCHAR(100) NOT NULL
);

CREATE TABLE Library (
    library_id INT IDENTITY(1,1) PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    founded_year INT,
    city_id INT NOT NULL,
    FOREIGN KEY (city_id) REFERENCES City(city_id)
);

CREATE TABLE Book (
    book_id INT IDENTITY(1,1) PRIMARY KEY,
    title VARCHAR(150) NOT NULL,
    publisher VARCHAR(100) NOT NULL,
    year INT NOT NULL
);

CREATE TABLE FairyTale (
    fairytale_id INT IDENTITY(1,1) PRIMARY KEY,
    title VARCHAR(150) NOT NULL,
    author_name VARCHAR(100) NOT NULL,
    written_year INT,
    pages INT,
    book_id INT NOT NULL,
    FOREIGN KEY (book_id) REFERENCES Book(book_id)
);

-- =========================
-- Books stored in Libraries
-- (many-to-many relationship)
-- =========================
CREATE TABLE LibraryBook (
    library_id INT NOT NULL,
    book_id INT NOT NULL,
    number_of_copies INT NOT NULL,
    register_date DATE NOT NULL,
    PRIMARY KEY (library_id, book_id),
    FOREIGN KEY (library_id) REFERENCES Library(library_id),
    FOREIGN KEY (book_id) REFERENCES Book(book_id)
);



