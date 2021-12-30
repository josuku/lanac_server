#include <iostream>
#include "../include/global.h"
#include "file_picker_interface.h"
#include "file_picker_cmd.h"

using namespace std;

FilePickerCmd::FilePickerCmd() { 
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
   string strPath;
   int option = 0;
   do
   {
      cout << "Select one of the example folders, or the option to introduce a manual path:" << endl;
      cout << " 1. " + SRC_FOLDER + "/client/images/folder1" << endl;
      cout << " 2. " + SRC_FOLDER + "/client/images/folder2" << endl;
      cout << " 3. " + SRC_FOLDER + "/client/images/folder3" << endl;
      cout << " 4. Manual full path" << endl;
      cout << "Selected: ";
      cin >> option;

      switch (option) {
         case 1:
            strPath = SRC_FOLDER + "/client/images/folder1";
            break;
         case 2:
            strPath = SRC_FOLDER + "/client/images/folder2";
            break;
         case 3:
            strPath = SRC_FOLDER + "/client/images/folder3";
            break;
         case 4:
            cout << "Please introduce a manual full path: ";
            cin >> strPath;
            break;
         default:
            cout << "Please, introduce a valid option" << endl;
            break;
      }
   } 
   while (option < 1 || option > 4);

   return strPath;
}
