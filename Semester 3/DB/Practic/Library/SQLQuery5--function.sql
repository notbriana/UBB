CREATE OR ALTER FUNCTION CountLibrariesInCluj()
RETURNS INT
AS
BEGIN
    DECLARE @cnt INT;
    SELECT @cnt = COUNT(*)
    FROM Library l
    INNER JOIN City c ON l.city_id = c.city_id
    WHERE c.name = 'Cluj-Napoca';
    RETURN @cnt;
END;



