#include <iostream>
#include "../include/global.h"
#include "file_picker_interface.h"
#include "file_picker_cmd.h"

using namespace std;

FilePickerCmd::FilePickerCmd(string srcPath) { 
   this->srcPath = srcPath;
}

FilePickerCmd::~FilePickerCmd() {
}

std::string FilePickerCmd::selectFile() 
{
   // TODO
   return "";
}

string FilePickerCmd::selectFolder() 
{
   string fullStrPath;
   int option = 0;
   do
   {
      cout << "Select one of the example folders, or the option to introduce a manual path:" << endl;
      cout << " 1. " + srcPath + "/client/images/folder1" << endl;
      cout << " 2. " + srcPath + "/client/images/folder2" << endl;
      cout << " 3. " + srcPath + "/client/images/folder3" << endl;
      cout << " 4. Manual full path" << endl;
      cout << "Selected: ";
      cin >> option;

      switch (option) {
         case 1:
            fullStrPath = srcPath + "/client/images/folder1";
            break;
         case 2:
            fullStrPath = srcPath + "/client/images/folder2";
            break;
         case 3:
            fullStrPath = srcPath + "/client/images/folder3";
            break;
         case 4:
            cout << "Please introduce a manual full path: ";
            cin >> fullStrPath;
            break;
         default:
            cout << "Please, introduce a valid option" << endl;
            break;
      }
   } 
   while (option < 1 || option > 4);

   return fullStrPath;
}
