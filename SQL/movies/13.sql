SELECT DISTINCT(name) FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies ON movies.id = stars.movie_id
WHERE movies.title IN (SELECT DISTINCT(title) FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON people.id = stars.person_id
WHERE people.name = "Kevin Bacon"
AND people.birth = 1958)
AND people.name != "Kevin Bacon";