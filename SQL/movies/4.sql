SELECT COUNT(title) FROM movies
JOIN ratings ON movies.id = ratings.movie_id
AND ratings.rating >= 10.0;