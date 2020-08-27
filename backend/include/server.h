#ifndef SERVER_H
#define SERVER_H

#include <libwebsockets.h>
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <iniparser.h>

#include "global.h"
// #define SIZE 100

// Declaracion de funcion para realizar push-pop

// void push(long element);
// int  pop();

// Creacion de pila (100 de capacidad)

// extern long stack[SIZE];

// Inicializacion

// extern int top;

// Declaracion de variables

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

// Declaracion y seteo de MySQL

char query[MAX_STRING];
char messagefull[MAX_STRING];
char query2[MAX_STRING];
char username[MAX_STRING];
char iscontact[MAX_STRING];
char message[MAX_STRING];
char contact[MAX_STRING];

int explode(char ***arr_ptr, char *str, char delimiter);
static int callback_http(struct lws *wsi,
                         enum lws_callback_reasons reason, void *user,
                         void *in, size_t len);
static int callback_dumb_increment(struct lws *wsi,
                                   enum lws_callback_reasons reason,
                                   void *user, void *in, size_t len);
                            
void read_data();


#endif /* SERVER_H */
