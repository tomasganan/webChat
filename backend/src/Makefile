# Compilación programa principal

MYSQL_LIBS := $(shell mysql_config --libs)
MYSQL_CONF := $(shell mysql_config --cflags)

all:
	gcc server.c funciones.c $(MYSQL_CONF) $(MYSQL_LIBS) -L/usr/local/lib -lwebsockets -o server