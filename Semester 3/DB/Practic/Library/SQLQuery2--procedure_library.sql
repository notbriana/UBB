USE LibraryBookDB;
GO

CREATE OR ALTER PROCEDURE AddBookToLibrary
    @library_id INT,
    @book_id INT,
    @number_of_copies INT,
    @register_date DATE
AS
BEGIN
    IF EXISTS (
        SELECT 1
        FROM LibraryBook
        WHERE library_id = @library_id
          AND book_id = @book_id
    )
    BEGIN
        UPDATE LibraryBook
        SET number_of_copies = @number_of_copies,
            register_date = @register_date
        WHERE library_id = @library_id
          AND book_id = @book_id;
    END
    ELSE
    BEGIN
        INSERT INTO LibraryBook (library_id, book_id, number_of_copies, register_date)
        VALUES (@library_id, @book_id, @number_of_copies, @register_date);
    END
END;


INSERT INTO City (name, county, country)
VALUES ('Cluj-Napoca', 'Cluj', 'Romania');


INSERT INTO Library (name, founded_year, city_id)
VALUES ('Central Library', 1900, 1);

INSERT INTO Book (title, publisher, year)
VALUES ('Eternal Fairy Tales', 'MyPublisher', 2000);

SELECT * FROM LibraryBook;

EXEC AddBookToLibrary
    @library_id = 1,
    @book_id = 1,
    @number_of_copies = 10,
    @register_date = '2025-01-01';
