#include "server.h"

char *server, *userdb, *password, *database;
char *ip;
int port;

int explode(char ***arr_ptr, char *str, char delimiter){
  char *src = str, *end, *dst;
  char **arr;
  int size = 1, i;
  

  while ((end = strchr(src, delimiter)) != NULL){
      ++size;
      src = end + 1;
  }

  arr = malloc(size * sizeof(char *) + (strlen(str) + 1) * sizeof(char));
  src = str;
  dst = (char *) arr + size * sizeof(char *);

  for (i = 0; i < size; ++i){
      if ((end = strchr(src, delimiter)) == NULL)
        end = src + strlen(src);
      arr[i] = dst;
      strncpy(dst, src, end - src);
      dst[end - src] = '\0';
      dst += end - src + 1;
      src = end + 1;
  }
  *arr_ptr = arr;

  return size;
}

static int callback_http(struct lws *wsi,
                         enum lws_callback_reasons reason, void *user,
                         void *in, size_t len){
	return 0;
}

static int callback_dumb_increment(struct lws *wsi,
                                   enum lws_callback_reasons reason,
                                   void *user, void *in, size_t len){
    long wsi_adress = wsi; // El WSI seria como el puntero a la instancia de un websocket  
    conn = mysql_init(NULL); // Declaracion de variable para la dB

    // Conexion a la base de datos
    if (!mysql_real_connect(conn, server, userdb, password, database, port, NULL, 0)){
        fprintf(stderr, "%s\n", mysql_error(conn)); // En caso de error, lo comunica
        exit(1);
    }

    switch (reason) {
        case LWS_CALLBACK_ESTABLISHED:
            printf("Conexion establecida. \n");
            break;

        case LWS_CALLBACK_CLOSED: { // Fin sesion del websocket
            snprintf(query, MAX_STRING, "DELETE FROM users WHERE token=%lu", wsi_adress);
            if (mysql_query(conn, query)) {
                    fprintf(stderr, "%s\n", mysql_error(conn));
            }
            
            // Reseteo contacto
            reset_contact(len);


          printf("FIN DE SESION.\n");
        }

        case LWS_CALLBACK_RECEIVE: { // Creacion de buffer para almacenar respuesta
            if(!(char *) in) {
                return;
            }
            unsigned char *buf = (unsigned char*) malloc(LWS_SEND_BUFFER_PRE_PADDING + len + LWS_SEND_BUFFER_POST_PADDING);
            int i;

            for (i=0; i < len; i++) {
                buf[LWS_SEND_BUFFER_PRE_PADDING + (len - 1) - i ] = ((char *) in)[i];
            }

            // Guardar usuario
            int n;
            int len;
            char *out = NULL;
            char listContact[MAX_STRING] = {0};

            // Enviar consulta SQL
            char **arr;
            char **arr2;
            char isUserNameString[MAX_STRING] = {0};
            char contact[MAX_STRING] = {0};
            char from[MAX_STRING] = {0};
            char to[MAX_STRING] = {0};
            char date[MAX_STRING] = {0};
            char msj[MAX_STRING] = {0};
            strncpy(isUserNameString, (char *) in, 11);
            isUserNameString[11] = '\0';;

            if(strcmp("firstnamews", isUserNameString) == 0) {
                explode(&arr, (char *) in, ':');
                snprintf(username, MAX_STRING, "%s",  arr[1]);
                free(arr);
                snprintf(query, MAX_STRING, "INSERT INTO users (name, token) VALUES ('%s', '%lu')",  username, wsi_adress);

                if (mysql_query(conn, query)) {
                    fprintf(stderr, "%s\n", mysql_error(conn)); 
                    len = strlen(mysql_error(conn));
                    out = (char *)malloc(sizeof(char)*(LWS_SEND_BUFFER_PRE_PADDING + len + LWS_SEND_BUFFER_POST_PADDING));
                    // Configuracion del buffer
                    memcpy (out + LWS_SEND_BUFFER_PRE_PADDING, mysql_error(conn), len );
                    lws_write(wsi,  out + LWS_SEND_BUFFER_PRE_PADDING, len, LWS_WRITE_TEXT);
                    free(out);
                    break;
                }

                // Reseteo contacto
                reset_contact(len);
            } else {
               // Enviar mensaje
                        explode(&arr2, (char *) in, ':'); // Separo el array con dos puntos
                        snprintf(iscontact, MAX_STRING, "%s",  arr2[0]);
                        snprintf(message, MAX_STRING, "%s",  arr2[2]);
                        snprintf(contact, MAX_STRING, "%s",  arr2[1]);
                        free(arr2);
                        snprintf(query, MAX_STRING, "SELECT * FROM users WHERE name='%s'",  contact); // Consulto a la dB por el user destinario

                        if (mysql_query(conn, query)) {
                                fprintf(stderr, "%s\n", mysql_error(conn));
                        }

                        res = mysql_store_result(conn);
                        char value[10];
                        char *eptr;
                        long long wsi_long;

                        while ((row = mysql_fetch_row(res)) != NULL) {
                            strcpy(value, row[1]);
                            snprintf(from, MAX_STRING, "%s", row[2]);
                            wsi_long = strtoll(value, &eptr, 10);
                        }

                        mysql_free_result(res);
                        snprintf(query, MAX_STRING, "SELECT * FROM users WHERE token='%lu'",  wsi);

                        if (mysql_query(conn, query)) {
                                fprintf(stderr, "%s\n", mysql_error(conn));
                        }

                        res = mysql_store_result(conn);

                        while ((row = mysql_fetch_row(res)) != NULL) {
                            snprintf(messagefull, MAX_STRING, "from:%s:%s", row[2],message);
                            len = strlen(messagefull);
                            snprintf(to, MAX_STRING, "%s", row[2]);
                            out = (char *)malloc(sizeof(char)*(LWS_SEND_BUFFER_PRE_PADDING + len + LWS_SEND_BUFFER_POST_PADDING));
                            // Configuracion del buffer
                            memcpy (out + LWS_SEND_BUFFER_PRE_PADDING, messagefull, len );
                            lws_write(wsi_long,  out + LWS_SEND_BUFFER_PRE_PADDING, len, LWS_WRITE_TEXT);
                            free(out);
                        }
                        mysql_free_result(res);
                        free(buf);
                        snprintf(msj, MAX_STRING, "%s", message);
                        snprintf(query, MAX_STRING, "INSERT INTO msj  (desde, recibe, mensaje) VALUES ('%s', '%s', '%s');", from, to, msj);
                        if (mysql_query(conn, query)) {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                        }
            }

            break;
        }
        default:
        break;
    }
    mysql_close(conn);
    return 0;
}

// Config. protocolo, nombre identificatorio del socket en el front

static struct lws_protocols protocols[] = {
    {
        "http-only",   // Protocolo
        callback_http, 
        0             
    },
    {/* dumb */
        "dumb-increment-protocol", // "ID" del socket para el front/
        callback_dumb_increment,    
        0                          
    },
    {
        NULL, NULL, 0   
    }
};

int main(int argc, char **argv) {
    
    read_data();


    // La URL del servidor será: http://localhost:9000
    conn = mysql_init(NULL);

    // Conexion a la base de datos
    if (!mysql_real_connect(conn, server, userdb, password, database, port, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    
    // snprintf(query, MAX_STRING, "USE chat;"); // Eliminacion de todos los user
    
    // if (mysql_query(conn, query)) {
    //     fprintf(stderr, "%s\n", mysql_error(conn));
    //     exit(1);
    // }
    

    snprintf(query, MAX_STRING, "TRUNCATE TABLE users;"); // Eliminacion de todos los user
    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);

    // Configuracion para la creacion del socketport
    struct lws_context *context;
    struct lws_context_creation_info context_info = {
        .port = port, .iface = NULL, .protocols = protocols, .extensions = NULL,
        .ssl_cert_filepath = NULL, .ssl_private_key_filepath = NULL, .ssl_ca_filepath = NULL,
        .gid = -1, .uid = -1, .options = 0, NULL, .ka_time = 0, .ka_probes = 0, .ka_interval = 0
    };

    context = lws_create_context(&context_info); // Crear conexion/contexto

    if (context == NULL) {
        fprintf(stderr, "LWS falló \n");
        return -1;
    }
    
    printf("Inicio de servidor...\n");
    
    while (1) {
        lws_service(context, 50); // Proceso de todos los eventos
    }
    
    lws_context_destroy(context); // Destruye la conexion
    
    return 0;
}

void read_data() {
  // IniParser

  char *nomFile = "src/config.ini";
  dictionary *ini = NULL;

  // Cargo archivo de configuracion .ini

  ini = iniparser_load(nomFile);

  server = iniparser_getstring(ini, "DATABASE:server", NULL);
  printf("%s\n", server);
  userdb = iniparser_getstring(ini, "DATABASE:userdb", NULL);
  printf("%s\n", userdb);
  password = iniparser_getstring(ini, "DATABASE:password", NULL);
  printf("%s\n", password);
  if(!strcmp(password, ""))
    password = NULL;

  database = iniparser_getstring(ini, "DATABASE:database", NULL);
  printf("%s\n", database);
  ip = iniparser_getstring(ini, "SERVER:ip", NULL);
  printf("%s\n", ip);
  port = iniparser_getint(ini, "SERVER:port", -1);
  printf("%d\n", port);

  iniparser_freedict(ini);
}