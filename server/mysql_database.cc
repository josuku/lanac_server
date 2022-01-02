#include <iostream>
#include <opencv2/core.hpp>
#include <mysqlx/xdevapi.h>
#include <ctime>
#include <exception>
#include "../include/global.h"
#include "picture_processing_interface.h"
#include "database_interface.h"
#include "mysql_database.h"
#include "file_repository_interface.h"

using namespace std;

MySQLDatabase::MySQLDatabase() : session(NULL), db(NULL), picturesTable(NULL)
{
   init();
}

MySQLDatabase::~MySQLDatabase()
{
   delete picturesTable;
   delete db;
   delete session;
}

void MySQLDatabase::init()
{
   string sqlServer = (getenv("MYSQL_SERVER") != NULL ? getenv("MYSQL_SERVER") : MYSQL_SERVER);
   string sqlUser = (getenv("MYSQL_USER") != NULL ? getenv("MYSQL_USER") : MYSQL_USER);
   string sqlPassword = (getenv("MYSQL_PASSWORD") != NULL ? getenv("MYSQL_PASSWORD") : MYSQL_PASSWORD);
   try 
   {
      session = new mysqlx::Session(sqlServer, 33060, sqlUser, sqlPassword);
      db = new mysqlx::Schema(*session, "lanaccess");
      picturesTable = new mysqlx::Table(*db, "pictures");
   }
   catch (exception& e)
   {
      cout << "[Server] ERROR: Can't establish connection to mysql server: " << e.what() << endl;
      exit(-1);
   }
}

int MySQLDatabase::save(string fileName, PictureProcessingInterface::Operation operation, string ipAddress) 
{
   time_t now = time(0);
   struct tm currentTime = *localtime(&now);
   char strCurrentTime[80];
   int id = 0;
   strftime(strCurrentTime, sizeof(strCurrentTime), "%Y-%m-%dT%X", &currentTime);

   cout << "[Server] Saving Picture on Database with following info" << endl;
   cout << "          - filename:" << fileName << endl;
   cout << "          - operation:" << (int)operation << endl;
   cout << "          - created_at:" << string(strCurrentTime) << endl;
   cout << "          - ip_address:" << ipAddress << endl;
   try 
   {
      mysqlx::Result result = picturesTable->insert("filename", "operation", "original_path", "processed_path", "created_at", "ip_address")
         .values(fileName, (int)operation, "", "", string(strCurrentTime), ipAddress).execute();
      id = result.getAutoIncrementValue();
      cout << "[Server] Inserted id is " << id << endl;
   } 
   catch (exception& e)
   {
      cout << "[Server] ERROR: Can't insert data into mysql server: " << e.what() << endl;
      exit(-1);
   }

   return id;
};

bool MySQLDatabase::updatePaths(int id, string originalPath, string processedPath)
{
   try 
   {
      mysqlx::Result result = picturesTable->update().set("original_path", originalPath).set("processed_path", processedPath)
         .where("id = " + to_string(id)).execute();
   } 
   catch (exception& e)
   {
      cout << "[Server] ERROR: Can't update data into mysql server: " << e.what() << endl;
      exit(-1);
   }
   cout << "[Server] Updated paths of id " << id << endl;
   return true;
}
