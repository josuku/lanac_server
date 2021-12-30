#include <iostream>

using namespace std;

#define BUFFER_LENGTH 512
#define MAX_FILE_SIZE 256
#define MAX_FILE_EXTENSION 5
#define MAX_CONNECTIONS 5
#define PORT 20000

const string SAVE_FOLDER = "/Users/josuku/Downloads/";
const string SRC_FOLDER = "/Volumes/DatosSSD/Developer/lanaccess";
const string MYSQL_SERVER = "192.168.1.100";
const string MYSQL_TABLE = "lanaccess";
const string MYSQL_USER = "lanaccess";
const string MYSQL_PASSWORD = "Lxnaccess1$";
const string IMAGE_EXTENSIONS = "jpg,jpeg,png";
const string NO_GUI_CLIENT_PARAMETER = "-nogui";

enum PictureProcessingOperation {
   NO_OPERATION = 0,
   ROTATE_90_LEFT = 1,
   ROTATE_90_RIGHT = 2
};

struct FileHeader {
   char name[MAX_FILE_SIZE];
   char extension[MAX_FILE_EXTENSION];
   PictureProcessingOperation operation;
};
