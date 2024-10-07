WITH sell AS (
    SELECT seller_id, COUNT(*) AS cnt FROM order_items
    WHERE price > 150
    GROUP BY seller_id
)
SELECT seller_id, cnt FROM sell
WHERE cnt > 100
ORDER BY cnt DESC
LIMIT 3;



