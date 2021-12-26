using namespace std;
using namespace cv;

class LocalFileRepository : public FileRepositoryInterface {
   public:
      string getTempPath();
      string getOriginalsPath();
      string getProcessedPath();

      string savePicture(Mat picture, string fullpath);
      string savePicture(Mat picture, string path, string filename);
      string movePicture(string originalFullPath, string newPath, string filename);
};
