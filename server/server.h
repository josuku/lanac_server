#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>

using namespace std;

class Server {
   public:
      Server(int port, int maxConnections);
      ~Server();
      bool createServer();
      bool acceptConnection();
      FileHeader receiveFileHeader();
      string receiveFile(string fileName);
      void disconnect();
   private:
      int serverPort;
      int maxConnections;
      int sockfd;
      int nsockfd;
};
