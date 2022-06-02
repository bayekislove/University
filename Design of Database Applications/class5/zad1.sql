USE Test

--SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED --dirty reads, non-repeatable reads, phantom reads
--SET TRANSACTION ISOLATION LEVEL READ COMMITTED --non-repeatable reads, phantom reads
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ --phantom reads
--SET TRANSACTION ISOLATION LEVEL SNAPSHOT
--SET TRANSACTION ISOLATION LEVEL SERIALIZABLE

--dirty reads
--transakcja 1
--BEGIN TRANSACTION
--UPDATE Towary SET NazwaTowaru='laptop' WHERE ID=1 
--WAITFOR DELAY '00:00:10'
--ROLLBACK TRANSACTION
--SELECT * FROM Towary WHERE ID=1

--transakcja 2 uruchomiona w tym samym czasie co pierwsza
--SELECT * FROM Towary WHERE ID=1

--non-repeatable reads
--transakcja 1, dane odczytane z poczatku tej transakcji beda pozniej zmienione
BEGIN TRANSACTION
SELECT * FROM Towary WHERE ID=1 
WAITFOR DELAY '00:00:10'
SELECT * FROM Towary WHERE ID=1 
COMMIT
GO

--transakcja 2
BEGIN TRANSACTION
UPDATE Towary SET NazwaTowaru = 'komputerek' WHERE ID=1
COMMIT

--phantom reads
--transakcja 1
--BEGIN TRANSACTION 
--SELECT * FROM imiona WHERE ID > 1
--WAITFOR DELAY '00:00:10'
--SELECT * FROM imiona WHERE ID > 1

--transakcja 2
--BEGIN TRANSACTION
--DELETE FROM imiona WHERE id=2
--COMMIT 