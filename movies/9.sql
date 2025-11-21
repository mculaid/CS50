SELECT name FROM people LEFT JOIN stars on people.id = stars.person_id INNER JOIN movies ON stars.movie_id = movies.id WHERE movies.year = 2004 GROUP BY people.name ORDER BY people.birth;
