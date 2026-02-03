CREATE OR ALTER PROCEDURE AddToWatchlist
    @account_id INT,
    @movie_id INT,
    @watched_date DATE
AS
BEGIN
    IF NOT EXISTS (
        SELECT 1
        FROM Watchlists
        WHERE account_id = @account_id
          AND movie_id = @movie_id
    )
    BEGIN
        INSERT INTO Watchlists (account_id, movie_id, watched_date)
        VALUES (@account_id, @movie_id, @watched_date);
    END
END;
GO
