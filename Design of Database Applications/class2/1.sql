SELECT DISTINCT addr.City FROM SalesLT.Address addr
WHERE EXISTS (SELECT 1 FROM SalesLT.SalesOrderHeader header 
			  WHERE header.ShipToAddressID = addr.AddressID) 
ORDER BY City DESC