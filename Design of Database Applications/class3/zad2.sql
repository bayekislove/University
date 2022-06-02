USE Test
DROP PROCEDURE IF EXISTS zapelnijDane
GO

CREATE PROCEDURE zapelnijDane @n int
AS
BEGIN
	DECLARE @i int
	SET @i = 0

	IF (@n > (((SELECT COUNT(DISTINCT imie) FROM imiona) * (SELECT COUNT(DISTINCT nazwisko) FROM nazwiska)) / 2))
	BEGIN
		;THROW 51111, 'Nieprawidlowe dane do zadania', 1;
	END

	DELETE FROM dane
	DECLARE @losoweNazwisko varchar(50)
	DECLARE @losoweImie varchar(50)

	WHILE @i < @n
	BEGIN
		SET @losoweNazwisko = (SELECT TOP 1 nazwisko FROM nazwiska ORDER BY NEWID())
		SET @losoweImie = (SELECT TOP 1 imie FROM imiona ORDER BY NEWID())
		IF NOT EXISTS (SELECT * FROM dane WHERE @losoweNazwisko = nazwisko AND @losoweImie = imie) 
			BEGIN
			INSERT INTO dane VALUES(@losoweImie, @losoweNazwisko)
			SET @i  = @i + 1
			END
	END

END
GO

EXEC zad2 @n = 3
GO