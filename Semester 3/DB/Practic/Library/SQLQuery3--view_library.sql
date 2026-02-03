CREATE OR ALTER VIEW FairyTalesInEternalBook
AS
SELECT ft.title
FROM FairyTale ft
INNER JOIN Book b ON ft.book_id = b.book_id
WHERE b.title = 'Eternal Fairy Tales';


INSERT INTO Book (title, publisher, year)
VALUES ('Short Stories', 'OtherPublisher', 2010);


INSERT INTO FairyTale (title, author_name, written_year, pages, book_id)
VALUES
('The Brave Little Tailor', 'Brothers Grimm', 1812, 32, 1), -- book_id = 1
('Hansel and Gretel', 'Brothers Grimm', 1812, 28, 1),       -- book_id = 1
('The Happy Prince', 'Oscar Wilde', 1888, 15, 2);           -- book_id = 2


SELECT * FROM FairyTalesInEternalBook;
