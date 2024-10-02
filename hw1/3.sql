SELECT customer_city AS city
FROM(
    SELECT COUNT(order_id) AS cnt, customer_city
    FROM(
        (SELECT customer_id, customer_state, customer_city FROM customers) AS cus 
        INNER JOIN
        (SELECT order_id, customer_id FROM orders) AS ord 
        ON cus.customer_id=ord.customer_id
    ) 
    WHERE customer_state LIKE 'RJ' 
    GROUP BY customer_city
) AS cnt_city
ORDER BY cnt DESC
LIMIT 3;
