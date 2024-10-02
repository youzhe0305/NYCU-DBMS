SELECT COUNT(py.order_id) AS cnt
FROM
    (SELECT order_id, payment_type FROM payments) as py,
    (SELECT customer_id, customer_state FROM customers) as cus,
    (SELECT order_id, customer_id, order_purchase_timestamp FROM orders) as ord
WHERE py.order_id=ord.order_id AND ord.customer_id=cus.customer_id 
AND payment_type LIKE 'debit_card' AND customer_state LIKE 'RJ' 
AND ord.order_purchase_timestamp LIKE '2017%';

