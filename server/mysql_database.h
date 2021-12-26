using namespace std;

class MySQLDatabase : public DatabaseInterface {
   public:
      MySQLDatabase();
      ~MySQLDatabase();
      void init();
      int save(string fileName, PictureProcessingInterface::Operation operation, string ipAddress);
      bool updatePaths(int id, string originalPath, string processedPath);
   private:
      mysqlx::Session* session;
      mysqlx::Schema* db;
      mysqlx::Table* picturesTable;
};
