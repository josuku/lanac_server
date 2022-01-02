#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <cstring>
#include "network_utils.h"

using namespace std;

string NetworkUtils::getValidIpAddress(const string &value)
{
   string ipAddress = "";
   if (!NetworkUtils::validateIpAddress(value) && !NetworkUtils::validateHostname(value, ipAddress)) 
   {
      cout << "Invalid IP address or hostname, try again" << endl;
   }
   else 
   {
      ipAddress = (ipAddress.length() > 0 ? ipAddress : value);
   }
   return ipAddress;
}

bool NetworkUtils::validateIpAddress(const string &ipAddress)
{
   struct sockaddr_in sa;
   int result = inet_pton(AF_INET, ipAddress.c_str(), &(sa.sin_addr));
   return result != 0;
}

bool NetworkUtils::validateHostname(const string &hostname, string &ipAddress)
{
   struct addrinfo hints, *res;
   memset(&hints, 0, sizeof(struct addrinfo));
   hints.ai_family = AF_INET;
   if (getaddrinfo(hostname.c_str(), NULL, &hints, &res) == 0 && res != NULL) 
   {
      char ipv4[INET_ADDRSTRLEN];
      struct sockaddr_in *addr4;
      
      for (; res != NULL; res = res->ai_next) 
      {
         if (res->ai_addr->sa_family == AF_INET) 
         {
               addr4 = (struct sockaddr_in *) res->ai_addr;
               inet_ntop(AF_INET, &addr4->sin_addr, ipv4, INET_ADDRSTRLEN);
               ipAddress = ipv4;
               return true;
         }
      }
   }
   return false;
}
