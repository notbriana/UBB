CREATE VIEW CustomerOrder AS
SELECT
    C.customer_id,
    C.email,
    COUNT(DISTINCT O.order_id) AS TotalOrders,
    MAX(O.order_date) AS LastOrderDate
FROM Customers C
LEFT JOIN Orders O ON C.customer_id = O.customer_id
GROUP BY C.customer_id, C.email
