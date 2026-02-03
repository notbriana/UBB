CREATE OR ALTER FUNCTION BooksInAllLibrariesFromCluj()
RETURNS TABLE
AS
RETURN
(
    SELECT b.title
    FROM Book b
    INNER JOIN LibraryBook lb ON b.book_id = lb.book_id
    INNER JOIN Library l ON lb.library_id = l.library_id
    INNER JOIN City c ON l.city_id = c.city_id
    WHERE c.name = 'Cluj-Napoca'
    GROUP BY b.book_id, b.title
    HAVING COUNT(DISTINCT l.library_id) = dbo.CountLibrariesInCluj()
);
