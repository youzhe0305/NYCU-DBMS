WITH py AS (
    SELECT payment_type, COUNT(order_id) AS cnt FROM payments
    GROUP BY payment_type
)
SELECT payment_type, cnt FROM py
WHERE cnt > 100
ORDER BY cnt DESC
LIMIT 1000
OFFSET 2;