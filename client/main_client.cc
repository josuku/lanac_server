#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
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
#include "network_utils.h"

using namespace std;
namespace fs = std::filesystem;

string getIpAddress() 
{
   string inputData, ipAddress;
   bool isValid = false;
   do 
   {
      cout << "Insert a valid IP address or hostname: ";
      cin >> inputData;
      ipAddress = NetworkUtils::getValidIpAddress(inputData);
   }
   while (ipAddress.length() > 0);
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

string getPicturesFolder(bool guiMode)
{
   cout << "[Client] Select a folder which include pictures, please" << endl;

   FilePickerInterface * filePicker = NULL;
   if (!guiMode)
   {
      string srcPath = (getenv("SRC_FOLDER") != NULL && std::strlen(getenv("SRC_FOLDER")) > 0 ? getenv("SRC_FOLDER") : SRC_FOLDER);
      filePicker = new FilePickerCmd(srcPath);
   }
   else 
   {
      filePicker = new FilePickerGui();
   }

   string folderPath = filePicker->selectFolder();
   if (folderPath.length() <= 0 || !fs::exists(folderPath))
   {
      cout << "[Client] Folder couldn't be opened or doesn't exist. Please, try again." << endl;
      return "";
   }

   cout << "[Client] Selected Folder is " << folderPath << endl;

   return folderPath;
}

// Main function. 
//  Parameters: 
//    -1. -nogui (optional): customizable value in NO_GUI_CLIENT_PARAMETER. activate command mode
//    -2. <hostname/ip> (optional): if -nogui is set, you can specify server hostname or ip address
//    -3. <processing_option> (optional): if -nogui is set, you can specify processing option to do with pictures (int value from PictureProcessingOperation)
//    -4. <pictures_folder> (optional): if -nogui is set, you can specify the folder of the pictures that will be processed
//  Environment Values:
//    - SRC_FOLDER (optional): folder where source code is placed. If no value is provided it will use include\global.h value
int main(int argc, char *argv[])
{
   string ipAddress, fileExtension, strFilePath, picturesFolderPath;
   bool fileProcessed = false;
   PictureProcessingOperation operation = PictureProcessingOperation::NO_OPERATION;

   bool nogui = (argc > 1 && std::strcmp(argv[1], NO_GUI_CLIENT_PARAMETER.c_str()) == 0);
   ipAddress = (argc > 2 && nogui ? NetworkUtils::getValidIpAddress(argv[2]) : getIpAddress());
   operation = (argc > 3 && nogui ? (PictureProcessingOperation)atoi(argv[3]) : getProcessingOperation());
   if (operation == PictureProcessingOperation::NO_OPERATION) return -1;
   picturesFolderPath = (argc > 4 && nogui && fs::exists(argv[4]) ? argv[4] : getPicturesFolder(!nogui));
   if (picturesFolderPath.length() == 0) return -1;

   for (const auto & entry : fs::directory_iterator(picturesFolderPath)) 
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
