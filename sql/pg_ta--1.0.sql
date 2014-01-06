-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION pg_ta" to load this file. \quit

CREATE OR REPLACE FUNCTION ta_f(
  IN ta_in double precision[],
  OUT ta_out double precision)
RETURNS SETOF double precision
AS 'pg_ta'
LANGUAGE C STRICT;

