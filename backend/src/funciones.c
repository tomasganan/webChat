#include "../include/header.h"

// Funcion para pushear nuevos elementos a la pila

extern int top;

void push(long element){
    if (top >= SIZE){
        printf("NO se puede agregar más elementos. \n");
        return;
    }
    top++; // Incrementar
    stack[top] = element; // Pushear
    printf("Datos pusheados OK. \n");
}

// Funcion pop

int pop(){
    if (top < 0){
        printf("Pila vacia.\n");
        return INT_MIN;
    }
    return stack[top--];
}

// Funcion reset

void reset_contact(int len) {
  // Reseteo contacto

  char contact[MAX_STRING] = {0};
  char reset[MAX_STRING] = {0};
  char *out = NULL;
  snprintf(query, MAX_STRING, "SELECT * FROM users");

  if (mysql_query(conn, query)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }
  res = mysql_store_result(conn);
  char value[10];
  char *eptr;
  long long wsi_long;
  while ((row = mysql_fetch_row(res)) != NULL) {
    strcpy(value, row[1]);
    wsi_long = strtoll(value, &eptr, 10);
    free(out);
    push(wsi_long);
  }
  mysql_free_result(res);

  snprintf(query, MAX_STRING, "SELECT * FROM users");

  if (mysql_query(conn, query)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }
  int i = 0;
  for (i = 0; i < top + 1; i++) {
    snprintf(reset, MAX_STRING, "reset");
    len = strlen(reset);
    out = (char *)malloc(sizeof(char) * (LWS_SEND_BUFFER_PRE_PADDING + len +
                                         LWS_SEND_BUFFER_POST_PADDING));
    // Configuracion del buffer
    memcpy(out + LWS_SEND_BUFFER_PRE_PADDING, reset, len);
    lws_write(stack[i], out + LWS_SEND_BUFFER_PRE_PADDING, len, LWS_WRITE_TEXT);
    free(out);
  }
  res = mysql_store_result(conn);
  int j = 0;
  while ((row = mysql_fetch_row(res)) != NULL) {
    for (j = 0; j < top + 1; j++) {
      snprintf(contact, MAX_STRING, "contact:%s", row[2]);
      len = strlen(contact);

      out = (char *)malloc(sizeof(char) * (LWS_SEND_BUFFER_PRE_PADDING + len +
                                           LWS_SEND_BUFFER_POST_PADDING));
      // Configuracion del buffer
      memcpy(out + LWS_SEND_BUFFER_PRE_PADDING, contact, len);
      lws_write(stack[j], out + LWS_SEND_BUFFER_PRE_PADDING, len,
                LWS_WRITE_TEXT);
      free(out);
    }
  }
  pop();

  mysql_free_result(res);
}