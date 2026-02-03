CREATE PROCEDURE GetCustomerOrder
    @customer_id INT
AS
BEGIN
    SELECT 
        C.name_customer,
        COUNT(DISTINCT O.order_id) AS TotalOrders,
        ISNULL(SUM(OI.quantity * B.price),0) AS TotalValue
    FROM Customers C
    LEFT JOIN Orders O ON C.customer_id = O.customer_id
    LEFT JOIN OrderItems OI ON O.order_id = OI.order_id
    LEFT JOIN Books B ON OI.book_id = B.book_id
    WHERE C.customer_id = @customer_id
    GROUP BY C.name_customer;
END


