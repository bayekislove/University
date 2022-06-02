DROP FUNCTION IF EXISTS LiczbaEgzemplarzyDlaCzytelnika
GO

CREATE FUNCTION LiczbaEgzemplarzyDlaCzytelnika(@dnie int) RETURNS TABLE
	RETURN SELECT PESEL, COUNT(Liczba_Dni) AS LiczbaEgzemparzy
	FROM dbo.Wypozyczenie, dbo.Czytelnik 
	WHERE Liczba_Dni > @dnie AND Czytelnik.Czytelnik_ID = Wypozyczenie.Czytelnik_ID
	GROUP BY PESEL
GO

SELECT * FROM LiczbaEgzemplarzyDlaCzytelnika(3)
GO