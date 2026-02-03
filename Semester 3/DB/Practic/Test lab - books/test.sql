CREATE DATABASE BookStoreDB

USE BookStoreDB

CREATE TABLE Bookstores (
    bookstore_id INT IDENTITY(1,1) PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    quantity INT NOT NULL 
);

CREATE TABLE Authors (
    author_id INT IDENTITY(1,1) PRIMARY KEY,
    name_author VARCHAR(100) NOT NULL
);

CREATE TABLE Books (
    book_id INT IDENTITY(1,1) PRIMARY KEY,
    title VARCHAR(100) NOT NULL,
    bookstore_id INT NOT NULL,
    author_id INT NOT NULL,
    price DECIMAL(10,2) NOT NULL,
    FOREIGN KEY (bookstore_id) REFERENCES Bookstores(bookstore_id),
    FOREIGN KEY (author_id) REFERENCES Authors(author_id)
);

CREATE TABLE Customers (
    customer_id INT IDENTITY(1,1) PRIMARY KEY,
    name_customer VARCHAR(100),
    email VARCHAR(100) UNIQUE NOT NULL
);

CREATE TABLE Orders (
    order_id INT IDENTITY(1,1) PRIMARY KEY,
    customer_id INT NOT NULL,
    order_date DATETIME DEFAULT GETDATE(),
    FOREIGN KEY (customer_id) REFERENCES Customers(customer_id)
);

CREATE TABLE OrderItems (
    order_item_id INT IDENTITY(1,1) PRIMARY KEY,
    order_id INT NOT NULL,
    book_id INT NOT NULL,
    quantity INT NOT NULL,
    FOREIGN KEY (order_id) REFERENCES Orders(order_id),
    FOREIGN KEY (book_id) REFERENCES Books(book_id)
);




