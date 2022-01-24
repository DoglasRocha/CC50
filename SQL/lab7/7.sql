SELECT AVG(energy) FROM songs s
JOIN artists a ON a.id = s.artist_id
WHERE a.name = 'Drake'