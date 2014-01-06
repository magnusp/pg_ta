MODULE_big   = pg_ta
OBJS         = $(patsubst %.c,%.o,$(wildcard src/*.c))
EXTENSION    = pg_ta
DATA         = sql/pg_ta--1.0.sql

PG_CPPFLAGS = -I/usr/include/ta-lib
SHLIB_LINK  = -L/usr/lib -lta_lib

PG_CONFIG    = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)

