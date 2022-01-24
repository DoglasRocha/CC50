SELECT name from SONGS
WHERE duration_ms > 60000 * 3
ORDER BY duration_ms DESC
LIMIT 5;