using namespace std;

class FilePickerGui : public FilePickerInterface
{
    public:
        FilePickerGui();
        ~FilePickerGui();
        string selectFile();
        string selectFolder();
    private:
        bool processResult(nfdresult_t& result, nfdchar_t** outhPath, string& strPath);
};
