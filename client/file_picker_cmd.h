using namespace std;

class FilePickerCmd : public FilePickerInterface
{
    public:
        FilePickerCmd();
        ~FilePickerCmd();
        string selectFile();
        string selectFolder();
};
