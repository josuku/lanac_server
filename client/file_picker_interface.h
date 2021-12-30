using namespace std;

class FilePickerInterface
{
    public:
        virtual string selectFile() = 0;
        virtual string selectFolder() = 0;
};
