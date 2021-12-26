#include <filesystem>
#include "file_picker.h"
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
   string ipAddress = getIpAddress();

   PictureProcessingOperation operation = getProcessingOperation();
   if (operation == PictureProcessingOperation::NO_OPERATION) return -1;

   cout << "Select a folder which include pictures, please" << endl;

   /*FilePicker filePicker;
   string filePath = filePicker.selectFile();
   if (filePath.length() <= 0) 
   {
      cout << "File couldn't be opened. Please, try again." << endl;
      return -1;
   }*/

   FilePicker filePicker;
   string folderPath = filePicker.selectFolder();
   if (folderPath.length() <= 0)
   {
      cout << "Folder couldn't be opened. Please, try again." << endl;
      return -1;
   }

   cout << "Selected Folder is " << folderPath << endl;

   for (const auto & entry : fs::directory_iterator(folderPath)) 
   {
      Client client (ipAddress, PORT);
      if (!client.connectToServer()) return -1;
      cout << "Processing " << entry.path() << endl;
      if (!client.sendFileHeader(entry.path(), operation)) return -1;
      if (!client.sendFile(entry.path())) return -1;
      client.disconnect();
   }

   return 0;
}
