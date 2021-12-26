#include <iostream>
#include <opencv2/core.hpp>
#include <mysqlx/xdevapi.h>
#include <ctime>
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
   session = new mysqlx::Session(MYSQL_SERVER, 33060, MYSQL_USER, MYSQL_PASSWORD);
   db = new mysqlx::Schema(*session, "lanaccess");
   picturesTable = new mysqlx::Table(*db, "pictures");
}

int MySQLDatabase::save(string fileName, PictureProcessingInterface::Operation operation, string ipAddress) 
{
   time_t now = time(0);
   struct tm currentTime = *localtime(&now);
   char strCurrentTime[80];
   strftime(strCurrentTime, sizeof(strCurrentTime), "%Y-%m-%dT%X", &currentTime);

   cout << "[Server] Saving Picture on Database with following info" << endl;
   cout << "          - filename:" << fileName << endl;
   cout << "          - operation:" << (int)operation << endl;
   cout << "          - created_at:" << string(strCurrentTime) << endl;
   cout << "          - ip_address:" << ipAddress << endl;

   mysqlx::Result result = picturesTable->insert("filename", "operation", "original_path", "processed_path", "created_at", "ip_address")
      .values(fileName, (int)operation, "", "", string(strCurrentTime), ipAddress).execute();

   cout << "[Server] Inserted id is " << result.getAutoIncrementValue() << endl;

   return result.getAutoIncrementValue();
};

bool MySQLDatabase::updatePaths(int id, string originalPath, string processedPath)
{
   mysqlx::Result result = picturesTable->update().set("original_path", originalPath).set("processed_path", processedPath)
      .where("id = " + to_string(id)).execute();

   cout << "[Server] Updated paths of id " << id << endl;
   return true;
}
