#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <filesystem>
#include <nfd.h>
#include "../include/global.h"
#include "file_picker_interface.h"
#include "file_picker_gui.h"
#include "file_picker_cmd.h"
#include "client.h"

using namespace std;
namespace fs = std::filesystem;

bool validateIpAddress(const string &ipAddress)
{
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, ipAddress.c_str(), &(sa.sin_addr));
    return result != 0;
}

string getIpAddress() 
{
   string ipAddress;
   bool isValid = false;
   do 
   {
      cout << "Introduce a valid IP address: ";
      cin >> ipAddress;

      if (!validateIpAddress(ipAddress)) 
      {
         cout << "Invalid IP address, try again" << endl;
      }
      else 
      {
         isValid = true;
      }
   }
   while (!isValid);
   return ipAddress;
}

PictureProcessingOperation getProcessingOperation()
{
   int selectedOption = 0;
   do 
   {
      cout << "Which operation do you want to do which pictures?" << endl;
      cout << " 1. Rotate 90 degrees left" << endl;
      cout << " 2. Rotate 90 degrees right" << endl;
      cout << " 3. Exit" << endl;
      cout << "Selected: ";
      cin >> selectedOption;

      if (selectedOption < 1 || selectedOption > 3)
         cout << "Invalid Operation! Please, choose a valid operation" << endl;
   }
   while (selectedOption < 1 || selectedOption > 3);

   if (selectedOption == 3) return PictureProcessingOperation::NO_OPERATION;

   return (PictureProcessingOperation)selectedOption;
}

// Main function
int main(int argc, char *argv[])
{
   string ipAddress = getIpAddress(), fileExtension, strFilePath;
   bool fileProcessed = false;

   PictureProcessingOperation operation = getProcessingOperation();
   if (operation == PictureProcessingOperation::NO_OPERATION) return -1;

   cout << "[Client] Select a folder which include pictures, please" << endl;

   FilePickerInterface * filePicker = NULL;

   if (argc > 1 && std::strcmp(argv[1], NO_GUI_CLIENT_PARAMETER.c_str()) == 0)
   {
      filePicker = new FilePickerCmd();
   }
   else 
   {
      filePicker = new FilePickerGui();
   }

   string folderPath = filePicker->selectFolder();
   if (folderPath.length() <= 0 || !fs::exists(folderPath))
   {
      cout << "[Client] Folder couldn't be opened or doesn't exist. Please, try again." << endl;
      return -1;
   }

   cout << "[Client] Selected Folder is " << folderPath << endl;

   for (const auto & entry : fs::directory_iterator(folderPath)) 
   {
      strFilePath = string(entry.path());
      cout << "[Client] Processing " << strFilePath << endl;
      fileExtension = strFilePath.substr(strFilePath.find_last_of(".") + 1);

      if (string(IMAGE_EXTENSIONS).find(fileExtension, 0) != string::npos) {
         Client client (ipAddress, PORT);
         if (!client.connectToServer()) return -1;
         if (!client.sendFileHeader(strFilePath, fileExtension, operation)) return -1;
         if (!client.sendFile(entry.path())) return -1;
         client.disconnect();
         fileProcessed = true;
      }
   }

   if (!fileProcessed) {
      cout << "[Client] Folder selected doesn't have image files" << endl;
   }

   return 0;
}
