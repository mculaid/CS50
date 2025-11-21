SELECT AVG(rating) as average FROM ratings INNER JOIN movies on ratings.movie_id = movies.id WHERE year = 2012;
