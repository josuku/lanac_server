LANACCESS DEMO

C++ client to select a folder with pictures, choose an operation to do on the pictures and send data and files to the server.

C++ server to receive client's pictures, process the selected operation on them and save files on a file repository and additional data on a database.

PHP API Rest made with Lumen (Laravel) to access generated data by client and server.

Web View made with Lumn (Laravel) to show data from the API Rest.

PREREQUISITES:
   - Cmake: On MacOS you can install it with the command:
         $ brew install cmake
   - OpenCV: On MacOS you can install it with the command: 
         $ brew install opencv
   - MySQL Connector C++: On MacOS you can install it with the command: 
         $ brew install mysql-connector-c++
   * Depending on the installed versions, maybe you have to edit server CMakeLists to set correct folders for both libraries. On MacOS they should be installed in /usr/local/Cellar/
   * To install on MacOS you need to have installed Homebrew package manager.
 
USE:
   - Configure include/global.h parameters according to your needs.

   - Configure server's CMakeLists.txt file to set correct OpenCV_DIR, MYSQL_DIR and libmysqlcppconn8 library.

   - Generate a build with Cmake: from the root of the project:
      $ mkdir build_v1
      $ cd build_v1
      $ cmake ..
      $ cmake --build .

   - Server: Launch server without parameters. From build_v1 folder:
      $ ./server/server

   - Client: Launch client without parameters. From build_v1 folder:
      $ ./client/client

   - MySql: sql\mysql_lanaccess.sql script must be executed on a MySql server. MySql configuration must be set on include\global.h

   - Web_API: Must be installed in the same machine as Server, where files are stored. Web and API are made with Lumen-Laravel micro framework. web_api\.env file must be configured with correct values to access MySql database. To test web_api you can execute nexthe following command from web_api folder:
      $ php -S localhost:8000 -t public

API ROUTES:
   - /api/picture : Get data from all pictures

   - /api/picture/{id} : Get data from file with id {id} 

   - /api/picture/original/{id} : Get original picture from file with id {id}

   - /api/picture/processed/{id} : Get processed picture from file with id {id}
