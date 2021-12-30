using namespace std;

class Client {
   public:
      Client(string ipAddress, int port);
      ~Client();
      bool connectToServer();
      bool sendFileHeader(string filePath, string fileExtension, PictureProcessingOperation operation);
      bool sendFile(string filePath);
      void disconnect();
   private:
      string serverIpAddress;
      int serverPort;
      int sockfd;
};
