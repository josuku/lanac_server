#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include "../include/global.h"

using namespace std;

class Client {
   public:
      Client(string ipAddress, int port);
      ~Client();
      bool connectToServer();
      bool sendFileHeader(string filePath, string fileExtension, PictureProcessingOperation operation);
      bool sendFile(string filePath);
      void disconnect();
   private:
      string serverIpAddress;
      int serverPort;
      int sockfd;
};
