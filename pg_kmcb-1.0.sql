create function hostname()
returns text
as 'pg_kmcb','hostname'
language C immutable strict;
