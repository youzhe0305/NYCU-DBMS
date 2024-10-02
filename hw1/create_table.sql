CREATE TABLE customers(
    customer_id VARCHAR(50) NOT NULL,
    customer_unique_id VARCHAR(50),
    customer_zip_code_prefix INT DEFAULT 0,
    customer_city VARCHAR(50),
    customer_state VARCHAR(50),
    PRIMARY KEY (customer_id)
);

LOAD DATA LOCAL INFILE '/home/youzhe0305/hw1/hw1/geolocation.csv'
INTO TABLE customers
FIELDS TERMINATED BY ','
OPTIONALLY ENCLOSED BY '"'
LINES TERMINATED BY '\n'
IGNORE 1 LINES;

CREATE TABLE geolocation(
    geolocation_zip_code_prefix VARCHAR(50),
    geolocation_lat FLOAT NOT NULL,
    geolocation_lng FLOAT NOT NULL,
    geolocation_city VARCHAR(50),
    geolocation_state VARCHAR(50),
    PRIMARY KEY (geolocation_lat, geolocation_lng)
);

LOAD DATA LOCAL INFILE '/home/youzhe0305/hw1/hw1/geolocation.csv'
INTO TABLE geolocation
FIELDS TERMINATED BY ','
ENCLOSED BY '"'
LINES TERMINATED BY '\n'
IGNORE 1 LINES;

CREATE TABLE order_items(
    order_id VARCHAR(50) NOT NULL,
    order_item_id INT NOT NULL DEFAULT 0,   
    product_id VARCHAR(50),
    seller_id VARCHAR(50),
    shipping_limit_date DATETIME,
    price  FLOAT,
    freight_value FLOAT,
    PRIMARY KEY (order_id, order_item_id)
);

LOAD DATA LOCAL INFILE '/home/youzhe0305/hw1/hw1/order_items.csv'
INTO TABLE order_items
FIELDS TERMINATED BY ','
ENCLOSED BY '"'
LINES TERMINATED BY '\n'
IGNORE 1 LINES;

CREATE TABLE orders(
    order_id VARCHAR(50) NOT NULL,
    customer_id VARCHAR(50), 
    order_status VARCHAR(50),
    order_purchase_timestamp DATETIME DEFAULT NULL,
    order_approved_at DATETIME DEFAULT NULL,
    order_delivered_carrier_date DATETIME DEFAULT NULL,
    order_delivered_customer_date DATETIME DEFAULT NULL,
    order_estimated_delivery_date DATETIME DEFAULT NULL,
    PRIMARY KEY (order_id)
);

LOAD DATA LOCAL INFILE '/home/youzhe0305/hw1/hw1/orders.csv'
INTO TABLE orders
FIELDS TERMINATED BY ','
ENCLOSED BY '"'
LINES TERMINATED BY '\n'
IGNORE 1 LINES;

CREATE TABLE payments(
    order_id VARCHAR(50) NOT NULL,
    payment_sequential INT DEFAULT 0,
    payment_type VARCHAR(50),
    payment_installments INT DEFAULT 0,
    payment_value FLOAT,
    PRIMARY KEY(order_id)
);

LOAD DATA LOCAL INFILE '/home/youzhe0305/hw1/hw1/payments.csv'
INTO TABLE payments
FIELDS TERMINATED BY ','
ENCLOSED BY '"'
LINES TERMINATED BY '\n'
IGNORE 1 LINES;

CREATE TABLE products(
    product_id VARCHAR(50) NOT NULL,
    product_category VARCHAR(50),
    product_name_length INT DEFAULT 0,
    product_description_length INT DEFAULT 0,
    product_photos_qty INT DEFAULT 0,
    product_weight_g INT DEFAULT 0,
    product_length_cm INT DEFAULT 0,
    product_height_cm INT DEFAULT 0,
    product_width_cm INT DEFAULT 0,
    PRIMARY KEY(product_id)
);

LOAD DATA LOCAL INFILE '/home/youzhe0305/hw1/hw1/products.csv'
INTO TABLE products
FIELDS TERMINATED BY ','
ENCLOSED BY '"'
LINES TERMINATED BY '\n'
IGNORE 1 LINES;

CREATE TABLE sellers(
    seller_id VARCHAR(50) NOT NULL,
    seller_zip_code_prefix INT DEFAULT 0,
    seller_city VARCHAR(50),
    seller_state VARCHAR(50),
    PRIMARY KEY(seller_id)
);

LOAD DATA LOCAL INFILE '/home/youzhe0305/hw1/hw1/sellers.csv'
INTO TABLE sellers
FIELDS TERMINATED BY ','
ENCLOSED BY '"'
LINES TERMINATED BY '\n'
IGNORE 1 LINES;
