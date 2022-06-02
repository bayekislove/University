USE AdventureWorksLT2019
DROP TYPE IF EXISTS identyfikatoryy;
GO

CREATE TYPE identyfikatoryy AS TABLE
(identyfikator int);
GO

DROP PROCEDURE IF EXISTS uaktualnijDate;
GO

CREATE PROCEDURE uaktualnijDate @lista identyfikatoryy READONLY, @data DATE
AS
BEGIN
    IF ((SELECT COUNT(DiscontinuedDate)
         FROM SalesLT.Product
         INNER JOIN @lista ON SalesLT.Product.ProductID = identyfikator
         WHERE DiscontinuedDate IS NOT NULL) > 0)
			BEGIN
			;THROW 100000, 'Wykryto nienulla', 1;
			END
    ELSE
        BEGIN
            UPDATE SalesLT.Product
            SET DiscontinuedDate = @data
            FROM SalesLT.Product
            INNER JOIN @lista ON SalesLT.Product.ProductID = identyfikator
        END
END
GO

DECLARE @lista identyfikatoryy
INSERT INTO @lista VALUES(710)

DECLARE @data DATETIME
SET @data = GETDATE()

EXEC uaktualnijDate @lista, @data
GO