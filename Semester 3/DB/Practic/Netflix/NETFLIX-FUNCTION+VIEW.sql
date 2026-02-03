CREATE OR ALTER VIEW MoviesReviewedByActiveAccounts
AS
SELECT m.title
FROM Movies m
JOIN Reviews r ON m.movie_id = r.movie_id
JOIN (
    SELECT account_id
    FROM Watchlists
    GROUP BY account_id
    HAVING COUNT(*) > 3
) a ON r.account_id = a.account_id
GROUP BY m.movie_id, m.title
HAVING COUNT(DISTINCT r.account_id) >= 2;
GO

CREATE OR ALTER FUNCTION MoviesWatchedByRAccounts
(
    @R INT,
    @S DATE,
    @E DATE
)
RETURNS INT
AS
BEGIN
    DECLARE @result INT;

    SELECT @result = COUNT(*)
    FROM (
        SELECT movie_id
        FROM Watchlists
        WHERE watched_date BETWEEN @S AND @E
        GROUP BY movie_id
        HAVING COUNT(DISTINCT account_id) >= @R
    ) t;

    RETURN @result;
END;
GO
