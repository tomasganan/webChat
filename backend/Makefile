# Compilación programa principal

MYSQL_LIBS := $(shell mysql_config --libs)
MYSQL_CONF := $(shell mysql_config --cflags)
INC_DIRS := include/

all:
	gcc src/server.c src/funciones.c $(MYSQL_CONF) $(MYSQL_LIBS) -I$(INC_DIRS) -L/usr/local/lib -lwebsockets -o server