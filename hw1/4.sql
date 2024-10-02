SELECT order_id
FROM 
(SELECT order_id, DATEDIFF(order_delivered_customer_date, order_delivered_carrier_date) AS taken_time FROM orders
WHERE order_delivered_customer_date NOT LIKE '%0000/00/00 00:00:00%' 
 AND order_delivered_carrier_date NOT LIKE '%0000/00/00 00:00:00%' 
) AS ord
ORDER BY taken_time DESC 
LIMIT 3;