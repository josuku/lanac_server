#include "file_picker.h"

using namespace std;

FilePicker::FilePicker() { 
   NFD_Init();
}

FilePicker::~FilePicker() {
   NFD_Quit();
}

std::string FilePicker::selectFile() 
{
   string strPath;
   nfdchar_t *outPath;
   nfdfilteritem_t filterItem[1] = { { "Picture File", "jpg,jpeg,png" } };
   nfdresult_t result = NFD_OpenDialog(&outPath, filterItem, 1, NULL);
   if (this->processResult(result, &outPath, strPath)) 
   {
      return strPath;
   }
   return "";
}

string FilePicker::selectFolder() 
{
   string strPath;
   nfdchar_t *outPath;
   nfdresult_t result = NFD_PickFolderN(&outPath, NULL);
   if (this->processResult(result, &outPath, strPath)) 
   {
      return strPath;
   };
   return "";
}

bool FilePicker::processResult(nfdresult_t& result, nfdchar_t** outPath, string& strPath)
{
   if (result == NFD_OKAY)
   {
      strPath = std::string(*outPath);
      cout << "Success! Src is " << strPath << endl;
      NFD_FreePath(*outPath);
      return true;
   }
   else if (result == NFD_CANCEL)
   {
      cout << "User pressed cancel" << endl;
   }
   else 
   {
      cout << "Error: " << NFD_GetError() << endl;
   }
   return false;
} 
