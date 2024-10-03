WITH oct AS (SELECT order_id, customer_state, taken_time
    FROM
        (SELECT order_id, customer_id, UNIX_TIMESTAMP(order_delivered_customer_date) - UNIX_TIMESTAMP(order_delivered_carrier_date) AS taken_time
        FROM orders WHERE order_delivered_customer_date NOT LIKE '%0000/00/00 00:00:00%' 
        AND order_delivered_carrier_date NOT LIKE '%0000/00/00 00:00:00%' ) AS ord,
        (SELECT customer_id, customer_state FROM customers) AS cus
    WHERE ord.customer_id=cus.customer_id
)
SELECT mxt_state.customer_state, order_id
FROM 
    (SELECT MAX(taken_time) AS mxt, customer_state
    FROM oct
    GROUP BY customer_state) AS mxt_state,
    oct
WHERE mxt_state.mxt=oct.taken_time AND mxt_state.customer_state=oct.customer_state
ORDER BY mxt_state.customer_state DESC;


