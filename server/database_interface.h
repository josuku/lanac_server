using namespace std;

class DatabaseInterface {
   public:
      virtual void init() = 0;
      virtual int save(string fileName, PictureProcessingInterface::Operation operation, string ipAddress) = 0;
      virtual bool updatePaths(int id, string originalPath, string processedPath) = 0;
      virtual ~DatabaseInterface() = default;
};
