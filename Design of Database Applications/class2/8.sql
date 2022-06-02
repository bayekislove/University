-- listing all constraints 
--SELECT * 
--FROM INFORMATION_SCHEMA.CHECK_CONSTRAINTS

--adding a constraint
--ALTER TABLE SalesLT.SalesOrderHeader
--ADD CONSTRAINT zad8constraints CHECK ([ShipDate]>=[OrderDate] OR [ShipDate] IS NULL);

-- droping a constraint
-- ALTER TABLE SalesLT.SalesOrderHeader
-- DROP CONSTRAINT zad8constraint

-- updating element to a conflict with a constraint
UPDATE SalesLT.SalesOrderHeader
SET OrderDate = '2008/06/10' WHERE SalesOrderID = 71774

-- get all conflicting rows
SELECT *
FROM SalesLT.SalesOrderHeader
WHERE NOT ([ShipDate]>=[OrderDate] OR [ShipDate] IS NULL) --jak lepiej?