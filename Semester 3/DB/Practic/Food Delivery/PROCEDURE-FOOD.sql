CREATE OR ALTER PROCEDURE GetCustomerFoodAndBalance
	@customer_id INT
AS
BEGIN
	SELECT DISTINCT FI.food_name
	FROM Customers C
	JOIN Accounts A ON A.customer_id = C.customer_id
	JOIN Orders O ON O.account_id= A.account_id
	JOIN OrderItems OI ON OI.order_id = O.order_id
	JOIN FoodItems FI ON FI.food_id = OI.food_id
	WHERE C.customer_id = @customer_id AND O.order_type = 'ORDER';

	SELECT 
        A.initial_deposit - ISNULL(SUM(S.operation_amount), 0) AS money_left
    FROM Accounts A
    JOIN Orders O ON O.account_id = A.account_id
    JOIN Statistic S ON S.order_id = O.order_id
    WHERE A.customer_id = @customer_id
    GROUP BY A.initial_deposit;

END




EXEC GetCustomerFoodAndBalance 1;


