CREATE OR ALTER VIEW CustomerTransactionSummary  AS
SELECT C.customer_id, COUNT(O.order_id) AS NR_ORDERS, COUNT(R.order_id) AS NR_REFUNDS
FROM Customers C
LEFT JOIN Accounts A ON A.customer_id = C.customer_id
LEFT JOIN Orders O ON O.account_id = A.account_id AND O.order_type = 'ORDER'
LEFT JOIN Orders R ON R.account_id = A.account_id AND O.order_type = 'REFUND'
GROUP BY C.customer_id

SELECT * FROM CustomerTransactionSummary;
