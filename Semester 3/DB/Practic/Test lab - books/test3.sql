CREATE FUNCTION GetAuthorInfo
(
	@author_id INT
)
RETURNS TABLE
AS
RETURN
(
    SELECT 
        B.title,
        ISNULL(SUM(OI.quantity),0) AS TotalQuantityPerTitle
    FROM Books B
    LEFT JOIN OrderItems OI ON B.book_id = OI.book_id
    LEFT JOIN Orders O ON OI.order_id = O.order_id
    WHERE B.author_id = author_id
    GROUP BY B.title
)

