USE HealthDB;
GO

CREATE VIEW UserHealthStats2023 AS
SELECT
    u.name AS user_name,
    AVG(h.weight) AS average_weight,
    MAX(h.blood_pressure) AS max_blood_pressure
FROM Users u
JOIN HealthMetrics h ON u.user_id = h.user_id
WHERE YEAR(h.record_date) = 2023
GROUP BY u.name;
