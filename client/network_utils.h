using namespace std;

class NetworkUtils 
{
   public:
      static string getValidIpAddress(const string &value);
      static bool validateIpAddress(const string &ipAddress);
      static bool validateHostname(const string &hostname, string &ipAddress);
};
