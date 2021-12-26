#include "client.h"

Client::Client(string ipAddress, int port) 
{
   serverIpAddress = ipAddress;
   serverPort = port;
   sockfd = -1;
}

Client::~Client() 
{
   if (sockfd > 0) 
   {
      close (sockfd);
      cout << "[Client] Connection lost" << endl;
   }
}

bool Client::connectToServer() 
{
   struct sockaddr_in remote_addr;

   if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
   {
      cout << "[Client] ERROR: Failed to obtain Socket Descriptor, with errno:" << errno << endl;
      return false;
   }

   remote_addr.sin_family = AF_INET; 
   remote_addr.sin_port = htons(serverPort); 
   ::inet_pton(AF_INET, serverIpAddress.c_str(), &remote_addr.sin_addr); 
   bzero(&(remote_addr.sin_zero), 8);

   if (connect(sockfd, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)) == -1)
   {
      cout << "[Client] ERROR: Failed to connect to the host, with errno:" << errno << endl;
      return false;
   }
   cout << "[Client] Connected to server at port " << serverPort << endl;

   return true;
}

bool Client::sendFileHeader(string filePath, PictureProcessingOperation operation) 
{
   cout << "[Client] Sending file header of" << filePath << " to the Server... " << endl;

   FileHeader fileHeader;
   string fileName = filePath.substr(filePath.find_last_of("/") + 1);
   strcpy(fileHeader.name, fileName.c_str());
   fileHeader.operation = operation;

   if (send(sockfd, &fileHeader, sizeof(FileHeader), 0) < 0)
   {
      cout << "[Client] ERROR: Failed to send file header of file" << filePath << " with errno:" << errno << endl;
      return false;
   }

   cout << "[Client] File header correctly sent " << endl;
   return true;
}

bool Client::sendFile(string filePath) 
{
   cout << "[Client] Sending file " << filePath << " to the Server... " << endl;
   char buffer[BUFFER_LENGTH];
   size_t readLength;

   FILE *fs = fopen(filePath.c_str(), "r");
   if (fs == NULL)
   {
      cout << "[Client] ERROR: File " << filePath << " not found" << endl;
      return false;
   }

   bzero(buffer, BUFFER_LENGTH); 
   while ((readLength = fread(buffer, sizeof(char), BUFFER_LENGTH, fs)) > 0)
   {
      if (send(sockfd, buffer, readLength, 0) < 0)
      {
         cout << "[Client] ERROR: Failed to send file " << filePath << " with errno: " << errno << endl;
         return false;
      }
      bzero(buffer, BUFFER_LENGTH);
   }

   cout << "[Client] File " << filePath << " from Client WAS SENT!" << endl;
   return true;
}
        
void Client::disconnect()
{
   Client::~Client();
}
