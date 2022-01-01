using namespace std;

class FilePickerCmd : public FilePickerInterface
{
    public:
        FilePickerCmd(string srcPath);
        ~FilePickerCmd();
        string selectFile();
        string selectFolder();

    private:
        string srcPath;
};
