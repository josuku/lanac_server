#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <opencv2/core.hpp>
#include "../include/global.h"
#include "file_repository_interface.h"
#include "server.h"

Server::Server(int port, int connections)
{
   serverPort = port;
   maxConnections = connections;
   sockfd = -1;
}

Server::~Server() 
{
   if (sockfd > 0) 
   {
      close (sockfd);
      cout << "[Server] Connection lost on " << sockfd << endl;
   }
   if (nsockfd > 0) 
   {
      close (nsockfd);
      cout << "[Server] Connection lost on " << nsockfd << endl;
   }
}

bool Server::createServer() 
{
   struct sockaddr_in addr_local;

   if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
   {
      cout << "[Server] ERROR: Failed to obtain Socket Descriptor, with errno:" << errno << endl;
      return false;
   }

   cout << "[Server] Obtaining socket descriptor successfully" << endl;

   addr_local.sin_family = AF_INET;
   addr_local.sin_port = htons(serverPort);
   addr_local.sin_addr.s_addr = INADDR_ANY;
   bzero(&(addr_local.sin_zero), 8);

   if (::bind(sockfd, (struct sockaddr*)&addr_local, sizeof(struct sockaddr)) == -1 )
   {
      cout << "[Server] ERROR: Failed to bind Port, with errno:" << errno << endl;
      return false;
   }
   cout << "[Server] Binded tcp port " << serverPort << " in addr 127.0.0.1 sucessfully" << endl;

   if (listen(sockfd, maxConnections) == -1)
   {
      cout << "[Server] ERROR: Failed to listen Port, with errno:" << errno << endl;
      return false;
   }
   cout << "[Server] Listening the port " << serverPort << " successfully" << endl;
   return true;
}

string Server::acceptConnection() 
{
   struct sockaddr_in addr_remote;
   int sin_size = sizeof(struct sockaddr_in);

   if ((nsockfd = ::accept(sockfd, (struct sockaddr *)&addr_remote, (socklen_t *)&sin_size)) == -1) 
   {
      cout << "[Server] ERROR: Obtaining new Socket Despcritor, with errno:" << errno << endl;
      return "";
   }
   cout << "[Server] Server has got connected from " << inet_ntoa(addr_remote.sin_addr) << endl;

   char clientIpAddress[INET_ADDRSTRLEN];
   inet_ntop( AF_INET, &(addr_remote.sin_addr), clientIpAddress, INET_ADDRSTRLEN);
   return string(clientIpAddress);
}

FileHeader Server::receiveFileHeader() 
{
   FileHeader fileHeader;
   if (recv(nsockfd, &fileHeader, sizeof(FileHeader), 0) <= 0)
   {
      cout << "[Server] ERROR: Receiving File Header, with errno:" << errno << endl;
   }
   else
   {
      cout << "[Server] File Header received with name " << fileHeader.name << " and operation " << fileHeader.operation << endl;
   }
   return fileHeader;
}

string Server::receiveFile(string fileName, FileRepositoryInterface* fileRepository) 
{
   char buffer[BUFFER_LENGTH];
   size_t receivedLength = 0, writtenLength = 0;
   string savePath = fileRepository->getTempPath() + fileName;

   FILE* file = fopen(savePath.c_str(), "a");
   
   if (file == NULL)
   {
      cout << "[Server] ERROR: File " << savePath << " Cannot be opened file on server" << endl;
      return "";
   }
   else
   {
      bzero (buffer, BUFFER_LENGTH); 
      while ((receivedLength = recv (nsockfd, buffer, BUFFER_LENGTH, 0)) > 0) 
      {
         writtenLength = fwrite (buffer, sizeof(char), receivedLength, file);
         if (writtenLength < receivedLength)
         {
            cout << "[Server] ERROR: File write failed on server" << endl;
         }
         bzero (buffer, BUFFER_LENGTH);
         if (receivedLength == 0 || receivedLength != BUFFER_LENGTH) 
         {
            break;
         }
      }
      
      if (receivedLength < 0)
      {
         if (errno == EAGAIN)
         {
            cout << "[Server] ERROR: recv() timed out" << endl;
         }
         else
         {
            cout << "[Server] ERROR: recv() failed due to errno:" << errno << endl;
         }
         return "";
      }
      cout << "[Server] Received file from client!" << endl;
      fclose(file);
   }
   return savePath;
}
        
void Server::disconnect()
{
   Server::~Server();
}
