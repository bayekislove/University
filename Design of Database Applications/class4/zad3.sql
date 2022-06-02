DROP TRIGGER IF exists wyzwalacz
GO

CREATE TRIGGER wyzwalacz ON Bufor AFTER INSERT
AS
BEGIN
	DECLARE @dodaneID int, @dodanyAdres varchar(50), @dodanaData datetime

	SELECT TOP 1 @dodaneID = ID, @dodanyAdres = AdresUrl, @dodanaData = OstatnieWejscie FROM Bufor ORDER BY OstatnieWejscie DESC
	IF (SELECT COUNT(*) FROM Bufor WHERE @dodanyAdres = AdresUrl) > 1 --w buforze jest juz wystapienie
	BEGIN
		PRINT('w buforze wystapienie')
		DELETE FROM Bufor WHERE @dodaneID = ID
		UPDATE Bufor SET OstatnieWejscie = @dodanaData  WHERE @dodanyAdres = AdresUrl
	END

	ELSE --trzeba dodac do bufora, w buforze nie ma wystapienia
	BEGIN
		IF (SELECT COUNT(*) FROM Bufor) > CAST((SELECT wartosc FROM Parametry WHERE nazwa = 'max_cache') AS int) --czy przekroczony rozmiar bufora?
		BEGIN
			PRINT('przekroczony rozmiar bufora')
			SELECT TOP 1 @dodaneID = ID, @dodanyAdres = AdresUrl, @dodanaData = OstatnieWejscie FROM Bufor ORDER BY OstatnieWejscie ASC

			IF (SELECT COUNT(*) FROM Historia WHERE @dodanyAdres = AdresUrl) = 1 --czy w historii jest juz wpisany ten adres?
			BEGIN
				UPDATE Historia SET OstatnieWejscie = @dodanaData WHERE @dodanyAdres = AdresUrl --uaktualniamy stary adres
			END
			ELSE --przenosimy adres do historii
			BEGIN
				INSERT INTO Historia VALUES (@dodaneID, @dodanyAdres, @dodanaData)
			END

		DELETE FROM Bufor WHERE @dodaneID = ID --usuwamy wpis z bufora
		END
	END
END
GO

DELETE FROM Bufor
DELETE FROM Historia

INSERT INTO Bufor VALUES (2, 'www.a.com', DATEADD(DAY, -1, GETDATE()))
--SELECT * FROM Bufor
INSERT INTO Bufor VALUES (1, 'www.a.com', GETDATE())
--SELECT * FROM Bufor
INSERT INTO Bufor VALUES (3, 'www.b.com', DATEADD(DAY, 1, GETDATE()))
SELECT * FROM Bufor

INSERT INTO Bufor VALUES (4, 'www.c.com', DATEADD(DAY, 5, GETDATE()))
SELECT * FROM Bufor

INSERT INTO Bufor VALUES (5, 'www.d.com', DATEADD(DAY, 10, GETDATE()))
SELECT * FROM Bufor

SELECT * FROM Historia

INSERT INTO Bufor VALUES (8, 'www.a.com', DATEADD(YEAR, -10, GETDATE()))
SELECT * FROM Bufor

SELECT * FROM Historia
GO