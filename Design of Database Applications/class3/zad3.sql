DROP PROCEDURE IF EXISTS walidujCzytelnika
GO

CREATE PROCEDURE walidujCzytelnika (@nazwisko varchar(30), @PESEL char(11), @dataur date, @miasto varchar(30)) AS 
BEGIN
DECLARE @dataJakoString char(8)
SET @dataJakoString = CONVERT(char(8), @dataur, 112)

PRINT SUBSTRING(@dataJakoString, 5, 2)
PRINT SUBSTRING(@PESEL, 3, 2)
IF (LEN(@nazwisko) < 2)
	THROW 100000, 'Nazwisko musi miec dlugosc wieksza od 1!', 1;

IF (SUBSTRING(@nazwisko, 1, 1) = UPPER(SUBSTRING(@nazwisko, 1, 1)))
	THROW 100000, 'Nazwisko musi zaczynac sie od wielkiej litery!', 1;

IF (LEN(@PESEL) != 11)
	THROW 100000, 'PESEL musi miec dlugosc 11', 1;

IF (SUBSTRING(@dataJakoString, 3, 2) != SUBSTRING(@PESEL, 1, 2))
	THROW 100000, 'Rok w PESELu jest niepoprawny!', 1;

IF (SUBSTRING(@dataJakoString, 5, 2) != SUBSTRING(@PESEL, 3, 2))
	THROW 100000, 'Miesiac w PESELu jest niepoprawny!', 1;

IF (SUBSTRING(@dataJakoString, 7, 2) != SUBSTRING(@PESEL, 5, 2))
	THROW 100000, 'Dzien w PESELu jest niepoprawny!', 1;
--przepraszam za niezaimplementowanie calej walidacji
PRINT 'PESEL JEST POPRAWNY'
INSERT INTO Czytelnik (PESEL, Nazwisko, Data_Urodzenia, Miasto) VALUES(@PESEL, @nazwisko, @dataur, 'Szczecin')
END
GO

EXEC walidujCzytelnika @nazwisko = 'Nowak', @PESEL = '79111522232', @dataur = '1979-11-15', @miasto = 'Warszawa'
GO