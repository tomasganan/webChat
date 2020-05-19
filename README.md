## webChat (WebSocket + Angular)

_En el siguiente proyecto encontrará un sistema cliente-servidor para la administración de mensajeria instantánea. En el mismo se utilizaron diversas tecnologías para una mejor experiencia de usuario. Enjoy!_

### Inicio 🚀

_Estas instrucciones te permitirán obtener una copia del proyecto en funcionamiento en tu máquina local para propósitos de pruebas y evaluación._

- Descargar repositorio 

1. Instalar GIT (https://git-scm.com)
2. Clonar repositorio con el siguiente comando: 'git clone https://github.com/tomasganan/webChat.git'

### Instalación 🔧

- MySQL y Gestor de base de datos.

```
sudo apt-get update
sudo apt-get install mysql-server
sudo apt install libmysqlclient-dev
```

2. Instale el gestor de base de datos mas cómodo para usted (DBeaver, MySQL Workbench, etc)
3. Importe la base de datos que la encontrará en /backend/db/chat.sql.

- Libreria libwebsockets.org (BACKEND)

```
sudo apt-get install -y libwebsockets-dev
```

- Instalación de NodeJS + Angular (FRONTEND)
```
sudo apt install curl
curl -sL https://deb.nodesource.com/setup_10.x | sudo -E bash -
sudo apt install nodejs

sudo apt install npm
sudo npm install -g @angular/cli
```

(Versión NodeJS: 10.20.1 o posterior // Versión Angular: 9.1.0 o posterior)

### Ejecución ⚙️

- Backend (Servidor)

1. Ingresar al directorio /src.
2. Sobre la terminal de dicha carpeta ejecutar el comando "make all".
4. Ejecutar en la terminal "./server".

- Frontend (Cliente)

1. Ingresar a la carpeta 'frontend'.
1. Correr el comando ng s -o dentro de la misma.

### Construido con 🛠️

* **Libwebsocket** - Libreria utilizada para el Backend la cual fue seleccionada por su flexibilidad a la hora de implementar protocolos de red websocket.

* **Angular** - Framework utilizado para el Frontend el cual fue elegido por su estabilidad y simplicidad a la hora de escribirlo. Presenta ventajas como el 'ahorro de tiempo' ya que viene conformada la arquitectura de la aplicación, su organización, etc. Usa lenguaje 'TypeScript' lo que permite que la sintaxis y la forma de leer los códigos de la información sea siempre la misma.

* **MySQL** - Decidimos utilizar MySQL ya que es una base de datos muy rapida y es fácil de utilizar. Tiene innumerables ventajas como por ejemplo es 'Compatible con Linux y Windows', necesita 'Pocos requerimientos y eficiencia de memoria', entre otras.

### Autores ✒️

* **Tomás Gañan** - *Desarrollo inicial, Angular y Documentación*
* **Alexis Verardo** - *Desarrollo post-inicial, Angular e interfaz de usuario* 




