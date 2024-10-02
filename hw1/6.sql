SELECT order_id FROM orders
EXCEPT
SELECT order_id
FROM (SELECT order_id FROM orders) AS ord, (SELECT order_id AS poid FROM payments) AS py
WHERE order_id=poid;
