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

   - Generate a build with Cmake: from the root of the project:
      $ mkdir build_v1
      $ cd build_v1
      $ cmake ..
      $ cmake --build .

   - Server: Launch server without parameters. From build_v1 folder:
      $ ./server/server

   - Client: Launch client without parameters. From build_v1 folder:
      $ ./client/client

   - API: Must be installed in the same machine as Server, where files are stored.

   - MySql: sql\mysql_lanaccess.sql script must be executed on a MySql server. MySql configuration must be set on include\global.h
