# Compilación programa principal

programa: server.o
	gcc -o server `mysql_config --cflags` server.c `mysql_config --libs` -L/usr/local/lib -lwebsockets
