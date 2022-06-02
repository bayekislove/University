USE Test

DELETE FROM Ceny

INSERT INTO Ceny VALUES (2, 'zloty', 20)
INSERT INTO Ceny VALUES (2, 'euro', 100)
INSERT INTO Ceny VALUES (2, 'dolar', 70)

INSERT INTO Ceny VALUES (1, 'zloty', 4000)
INSERT INTO Ceny VALUES (1, 'funt', 20000)
INSERT INTO Ceny VALUES (1, 'euro', 17000)
INSERT INTO Ceny VALUES (1, 'frank', 15000)

INSERT INTO Ceny VALUES (3, 'zloty', 23)

ALTER TABLE Ceny NOCHECK CONSTRAINT ALL
INSERT INTO Ceny VALUES (1, 'korona', 10)
INSERT INTO Ceny VALUES (3, 'korona', 2)
ALTER TABLE Ceny CHECK CONSTRAINT ALL

--https://edux.pjwstk.edu.pl/mat/118/lec/w13.html

DECLARE cenyCursor CURSOR FOR SELECT TowarID, Waluta, Cena FROM Ceny
DECLARE @cursorTowarID int, @cursorWalutaCeny varchar(50), @cursorCena smallmoney
DECLARE @cenaPLN smallmoney
DECLARE @kursPLN smallmoney

OPEN cenyCursor
FETCH NEXT FROM cenyCursor INTO @cursorTowarID, @cursorWalutaCeny, @cursorCena

SET @cenaPLN = (SELECT Cena FROM Ceny WHERE TowarID = @cursorTowarID AND Waluta = 'zloty')
SET @kursPLN = (SELECT CenaPLN FROM Kursy WHERE Waluta = @cursorWalutaCeny)

WHILE @@FETCH_STATUS = 0
BEGIN 
	--PRINT(@cursorWalutaCeny)
	SET @cenaPLN = (SELECT Cena FROM Ceny WHERE TowarID = @cursorTowarID AND Waluta = 'zloty')
	IF NOT EXISTS (SELECT CenaPLN FROM Kursy WHERE Waluta = @cursorWalutaCeny)
		UPDATE Ceny 
		SET Cena = -1 
		WHERE TowarID = @cursorTowarID AND Waluta = @cursorWalutaCeny
	ELSE 
		UPDATE Ceny 
		SET Cena = @cenaPLN / (SELECT CenaPLN FROM Kursy WHERE Waluta = @cursorWalutaCeny)
		WHERE TowarID = @cursorTowarID AND Waluta = @cursorWalutaCeny
	FETCH NEXT FROM cenyCursor INTO @cursorTowarID, @cursorWalutaCeny, @cursorCena
END

CLOSE cenyCursor
DEALLOCATE cenyCursor

SELECT * FROM Ceny