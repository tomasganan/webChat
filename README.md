##### webChat (WebSocket + Angular) #####

- Descargar repositorio

1. Instalar GIT (https://git-scm.com)
2. Clonar repositorio con el siguiente comando: 'git clone https://github.com/tomasganan/webChat.git'

- MySQL y Gestor de base de datos

1. Para la instalación de MySQL se deberán correr los siguientes comandos:

sudo apt-get update
sudo apt-get install mysql-server

2. Instale el gestor de base de datos mas cómodo para usted (DBeaver, MySQL Workbench, etc)
3. Importe la base de datos que la encontrará en /backend/db/chat.sql.

##### BACKEND (Servidor) #####

- Instalación de la libreria libwebsockets.org

1. sudo apt-get install -y libwebsockets-dev

- Ejecución del backend (servidor)

1. Ingresar al directorio /src.
2. Sobre la terminal de dicha carpeta ejecutar el comando "make programa".
4. Ejecutar en la terminal "./server".

##### FRONTEND (Cliente) #####

- Instalación de NodeJS + Angular

1. sudo apt install nodejs
2. npm install -g @angular/cli

(Versión NodeJS: 10.20.1 o posterior // Versión Angular: 9.1.0 o posterior)

- Ejecución del frontend (cliente)

1. Ingresar a la carpeta 'frontend'.
1. Correr el comando ng s -o dentro de la misma.


