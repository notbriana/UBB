CREATE DATABASE FoodDelivery2DB


CREATE TABLE Customers(
	customer_id INT IDENTITY(1,1) PRIMARY KEY,
	name VARCHAR(100) NOT NULL
)

CREATE TABLE Accounts(
	account_id INT IDENTITY(1,1) PRIMARY KEY,
	customer_id INT UNIQUE NOT NULL,
	initial_deposit DECIMAL(10,2) NOT NULL,
	FOREIGN KEY (customer_id) REFERENCES Customers(customer_id)
);

CREATE TABLE FoodItems(
	food_id INT IDENTITY(1,1) PRIMARY KEY,
	food_name VARCHAR(100) NOT NULL,
	food_type VARCHAR(50) NOT NULL,
	price DECIMAL(10,2) NOT NULL
);

CREATE TABLE Orders (
    order_id INT IDENTITY(1,1) PRIMARY KEY,
    account_id INT NOT NULL,
    order_type VARCHAR(10) CHECK (order_type IN ('ORDER', 'REFUND')),
    order_date DATETIME2 NOT NULL DEFAULT SYSDATETIME(),
    FOREIGN KEY (account_id) REFERENCES Accounts(account_id)
);

CREATE TABLE OrderItems (
    order_id INT NOT NULL,
    food_id INT NOT NULL,
    quantity INT NOT NULL,
    PRIMARY KEY (order_id, food_id),
    FOREIGN KEY (order_id) REFERENCES Orders(order_id),
    FOREIGN KEY (food_id) REFERENCES FoodItems(food_id)
);

CREATE TABLE Statistic (
    order_id INT PRIMARY KEY,
    operation_amount DECIMAL(10,2) NOT NULL, -- positive for ORDER, negative for REFUND
    FOREIGN KEY (order_id) REFERENCES Orders(order_id)
);
