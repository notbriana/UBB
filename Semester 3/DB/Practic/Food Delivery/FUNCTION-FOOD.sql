CREATE FUNCTION OnlyPizzaCustomers()
RETURNS TABLE
AS
RETURN
(
	SELECT
		C.customer_id, COUNT(DISTINCT O.order_id) AS nr_transactions
	FROM Customers C
	JOIN Accounts A ON A.customer_id=C.customer_id
	JOIN Orders O ON O.account_id=A.account_id
	JOIN OrderItems OI ON OI.order_id=O.order_id
	JOIN FoodItems FI ON FI.food_id = OI.food_id
	GROUP BY C.customer_id
	HAVING MIN(FI.food_type) = 'Pizza' AND MAX(FI.food_type) = 'Pizza'
);

SELECT * FROM OnlyPizzaCustomers();
