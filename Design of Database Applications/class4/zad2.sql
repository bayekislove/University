USE Test

DROP PROCEDURE IF exists wyliczPensje
GO

DROP TABLE IF EXISTS Logs
GO
CREATE TABLE Logs (ID int, powod varchar(250))
GO

CREATE PROCEDURE wyliczPensje @miesiac int
AS
BEGIN
	DECLARE @zarobkiTab AS TABLE (ID int, wynagrodzenie int)
	DECLARE pracownikCursor CURSOR FOR SELECT ID, SalaryGross FROM Employees
	
	OPEN pracownikCursor
	DECLARE @ID int, @zarobki int
	FETCH NEXT FROM pracownikCursor INTO @ID, @zarobki

	WHILE (@@fetch_status=0)
	BEGIN
		DECLARE @sum int = 0, @brutto int
		DECLARE wyplataCursor CURSOR FOR SELECT SalaryGros FROM SalaryHistory WHERE EmployeeID = @ID 
		OPEN wyplataCursor
		FETCH NEXT FROM wyplataCursor INTO @brutto

		WHILE (@@fetch_status=0)
		BEGIN
			SET @sum = @sum + @brutto
			FETCH NEXT FROM wyplataCursor INTO @brutto
		END
		IF (SELECT COUNT(*) FROM SalaryHistory WHERE EmployeeID = @ID) < 12
		BEGIN
			INSERT INTO Logs VALUES(@ID, 'Nie mam jak wyliczyc wyplaty bo mniej niz 12 miesiecy')
		END
		ELSE
		BEGIN
			SET @brutto = (SELECT SalaryGros FROM SalaryHistory WHERE EmployeeID = @ID AND Month = @miesiac)
			PRINT(@brutto)
			IF @sum < 120000
			BEGIN
				INSERT INTO @zarobkiTab VALUES (@ID, @brutto - ((@sum * 0.17) / 12))
			END
			ELSE
			BEGIN
				INSERT INTO @zarobkiTab VALUES (@ID, @brutto - ((15300 + ((@sum - 120000) * 0.32)) / 12))
			END
		END
		FETCH NEXT FROM pracownikCursor INTO @ID, @zarobki
		CLOSE wyplataCursor
		DEALLOCATE wyplataCursor
	END
	CLOSE pracownikCursor
	DEALLOCATE pracownikCursor
	SELECT * FROM @zarobkiTab
	SELECT * FROM Logs
END
GO

DELETE FROM SalaryHistory
DELETE FROM Employees

INSERT INTO Employees VALUES (1, 7000)
INSERT INTO Employees VALUES (2, 1000)

INSERT INTO SalaryHistory VALUES (1, 1, 1, 4000, 7000)
INSERT INTO SalaryHistory VALUES (2, 1, 2, 4000, 8000) 
INSERT INTO SalaryHistory VALUES (3, 1, 3, 4000, 9000) 
INSERT INTO SalaryHistory VALUES (4, 1, 4, 4000, 4000) 
INSERT INTO SalaryHistory VALUES (5, 1, 5, 4000, 10000) 
INSERT INTO SalaryHistory VALUES (6, 1, 6, 4000, 7000) 
INSERT INTO SalaryHistory VALUES (7, 1, 7, 4000, 7000) 
INSERT INTO SalaryHistory VALUES (8, 1, 8, 4000, 7000) 
INSERT INTO SalaryHistory VALUES (9, 1, 9, 4000, 7000) 
INSERT INTO SalaryHistory VALUES (10, 1, 10, 4000, 7000) 
INSERT INTO SalaryHistory VALUES (11, 1, 11, 4000, 7000) 
INSERT INTO SalaryHistory VALUES (12, 1, 12, 4000, 7000) 

INSERT INTO SalaryHistory VALUES (13, 2, 4, 1000, 1000)

EXEC wyliczPensje @miesiac=4
