#include <stdio.h>
#include <stdlib.h>
#include <libwebsockets.h>
#include <mysql.h>
#define SIZE 100

// Creacion de pila (100 de capacidad)
long stack[SIZE];

// Inicializacion
int top = -1;

// Declaracion de variables
MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

// Declaracion y seteo de MySQL
char *server = "localhost";
char *userdb = "tomasito";
char *password = "Tomas_123"; // ¡Set!
char *database = "chat";
#define MAX_STRING 128
char query[MAX_STRING] = {0};
char messagefull[MAX_STRING] = {0};
char query2[MAX_STRING] = {0};
char username[MAX_STRING] = {0};
char iscontact[MAX_STRING] = {0};
char message[MAX_STRING] = {0};
char contact[MAX_STRING] = {0};