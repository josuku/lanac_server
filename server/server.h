using namespace std;

class Server {
   public:
      Server(int port, int maxConnections);
      ~Server();
      bool createServer();
      string acceptConnection();
      FileHeader receiveFileHeader();
      string receiveFile(string fileName, FileRepositoryInterface* fileRepository);
      void disconnect();
   private:
      int serverPort;
      int maxConnections;
      int sockfd;
      int nsockfd;
};
