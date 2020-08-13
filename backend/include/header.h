#include <libwebsockets.h>
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

// Declaracion de funcion para realizar push-pop

void push(long element);
int  pop();

// Creacion de pila (100 de capacidad)

extern long stack[SIZE];

// Inicializacion

extern int top;

// Declaracion de variables

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

// Declaracion y seteo de MySQL

#define MAX_STRING 128
char query[MAX_STRING];
char messagefull[MAX_STRING];
char query2[MAX_STRING];
char username[MAX_STRING];
char iscontact[MAX_STRING];
char message[MAX_STRING];
char contact[MAX_STRING];