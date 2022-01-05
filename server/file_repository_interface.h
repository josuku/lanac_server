using namespace std;
using namespace cv;

class FileRepositoryInterface {
   public:
      virtual string getTempPath() = 0;
      virtual string getOriginalsPath() = 0;
      virtual string getProcessedPath() = 0;

      virtual string savePicture(Mat picture, string fullpath, string &error) = 0;
      virtual string savePicture(Mat picture, string path, string filename, string &error) = 0;
      virtual string movePicture(string originalFullPath, string newPath, string filename) = 0;
      virtual ~FileRepositoryInterface() = default;
};
