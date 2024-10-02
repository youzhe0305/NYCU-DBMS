SELECT customer_state AS state, COUNT(order_id) AS cnt
FROM(
    (SELECT customer_id, customer_state, customer_city FROM customers) AS cus 
    INNER JOIN
    (SELECT order_id, customer_id FROM orders WHERE order_status!='delivered') AS ord 
    ON cus.customer_id=ord.customer_id
) 
GROUP BY customer_state;
