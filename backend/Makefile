# Compilación programa principal

MYSQL_LIBS := $(shell mysql_config --libs)
MYSQL_CONF := $(shell mysql_config --cflags)
INC_DIRS := include/
INC_PARSER := lib/iniparser/src/
SRC = src/server.c src/funciones.c
LIB_SRC = lib/iniparser/src/dictionary.c  lib/iniparser/src/iniparser.c


all:
	gcc $(SRC) $(LIB_SRC) $(MYSQL_CONF) $(MYSQL_LIBS) -I$(INC_DIRS) -I$(INC_PARSER) -L/usr/local/lib -lwebsockets -o server