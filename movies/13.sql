SELECT DISTINCT p2.name FROM people p1
INNER JOIN stars s1 ON	p1.id = s1.person_id
INNER JOIN stars s2 ON s1.movie_id = s2.movie_id
INNER JOIN people p2 ON p2.id = s2.person_id
WHERE p1.name = 'Kevin Bacon'
AND p1.birth = 1958
AND p2.id != p1.id;
