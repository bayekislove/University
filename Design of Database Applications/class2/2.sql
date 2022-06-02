SELECT model.Name, COUNT(product.ProductID) AS "Counter"
FROM SalesLT.ProductModel model, SalesLT.Product product
WHERE model.ProductModelID = product.ProductModelID
GROUP BY model.Name HAVING COUNT(product.ProductID) > 1