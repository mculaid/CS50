SELECT DISTINCT movies.title FROM movies
INNER JOIN ratings ON movies.id = ratings.movie_id
INNER JOIN stars ON movies.id = stars.movie_id
INNER JOIN people ON people.id = stars.person_id
WHERE people.name = 'Chadwick Boseman' ORDER by ratings.rating DESC LIMIT 5;
