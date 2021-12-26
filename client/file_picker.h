#include <iostream>
#include <nfd.h>

using namespace std;

class FilePicker
{
    public:
        FilePicker();
        ~FilePicker();
        string selectFile();
        string selectFolder();
    private:
        bool processResult(nfdresult_t& result, nfdchar_t** outhPath, string& strPath);
};
