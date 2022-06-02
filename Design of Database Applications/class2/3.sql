SELECT addr.City, COUNT(custAddr.CustomerID) AS 'Customers', COUNT(DISTINCT cust.SalesPerson) AS 'SalesPeople'
FROM SalesLT.Address addr, SalesLT.CustomerAddress custAddr, SalesLT.Customer cust
WHERE addr.AddressID = custAddr.AddressID AND cust.CustomerID = custAddr.AddressID
GROUP BY addr.City