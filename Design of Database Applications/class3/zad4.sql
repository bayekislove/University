USE Test
DROP PROCEDURE IF EXISTS przezIleWypozyczalKsiazke;
GO

DROP TYPE IF EXISTS identyfikatory;
GO

CREATE TYPE identyfikatory AS TABLE
(identyfikator int);
GO

DROP TYPE IF EXISTS sumaDni;
GO

CREATE TYPE sumaDni AS TABLE (
    czytelnik_id int, 
    suma_dni int);
GO

CREATE PROCEDURE przezIleWypozyczalKsiazke @Lista identyfikatory READONLY
AS
BEGIN
    SELECT Czytelnik_ID, SUM(Liczba_dni) AS Suma_Dni FROM Wypozyczenie
    INNER JOIN @Lista ON identyfikator = Czytelnik_ID
    GROUP BY Czytelnik_ID
END
GO

DECLARE @lista identyfikatory
INSERT INTO @lista VALUES(2)
INSERT INTO @lista VALUES(3)

EXEC przezIleWypozyczalKsiazke @lista
GO