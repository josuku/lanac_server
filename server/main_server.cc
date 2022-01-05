#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <mysqlx/xdevapi.h>
#include <opencv2/core/utils/filesystem.hpp>
#include "../include/global.h"
#include "file_repository_interface.h"
#include "local_file_repository.h"
#include "picture_processing_interface.h"
#include "picture_rotation_90_left.h"
#include "picture_rotation_90_right.h"
#include "server.h"
#include "database_interface.h"
#include "mysql_database.h"

using namespace cv;
using namespace std;

bool processPictureChange(PictureProcessingInterface::Operation operation, string pictureFullPath, Mat& processedPicture) 
{
   PictureProcessingInterface * pictureOperation = NULL;
   Mat originalPicture;
   originalPicture = imread(pictureFullPath, IMREAD_COLOR);
   switch (operation) 
   {
      case PictureProcessingInterface::Operation::ROTATE_90_LEFT:
         pictureOperation = new PictureRotation90Left();
         break;
      case PictureProcessingInterface::Operation::ROTATE_90_RIGHT:
         pictureOperation = new PictureRotation90Right();
         break;
      default:
         cout << "Error: Operation not recognized (" << operation << ")" << endl;
         return false;
   }
   processedPicture = pictureOperation->process(originalPicture);
   return true;
}

// Main function. 
//  Parameters: 
//
//  Environment Values:
//    - SAVE_FOLDER (optional): folder where pictures would be stored. If no value is provided it will use include\global.h value
//    - MYSQL_SERVER (optional): IP or hostname of MySQL server. If no value is provided it will use include\global.h value
//    - MYSQL_USER (optional): User of MySQL server. If no value is provided it will use include\global.h value
//    - MYSQL_PASSWORD (optional): Password for the user of MySQL server. If no value is provided it will use include\global.h value
int main(int argc, char *argv[])
{
   string localFileRepoPath = (getenv("SAVE_FOLDER") != NULL && std::strlen(getenv("SAVE_FOLDER")) > 0 ? getenv("SAVE_FOLDER") : SAVE_FOLDER);
   FileRepositoryInterface* fileRepository = new LocalFileRepository(localFileRepoPath);
   DatabaseInterface* storage = new MySQLDatabase();

   Server server(PORT, MAX_CONNECTIONS);
   if (!server.createServer()) return -1;
   while (true)
   {
      // Get File and Header from client
      string clientIpAddress = server.acceptConnection();
      if (clientIpAddress == "") return -1;
      FileHeader fileHeader = server.receiveFileHeader();
      if (strlen(fileHeader.name) == 0) return -1;
      string tempFilePath = server.receiveFile(fileHeader.name, fileRepository);
      if (tempFilePath.length() == 0) return -1;
      
      // Save basic info into storage
      int insertedId = storage->save(fileHeader.name, fileHeader.operation, clientIpAddress);

      // Process operation over the original picture
      Mat processedPicture;
      processPictureChange(fileHeader.operation, tempFilePath, processedPicture);
      
      // Save picture's to repository
      string error = "";
      string newPictureName = to_string(insertedId) + "." + fileHeader.extension;
      string processedFullPath = fileRepository->savePicture(processedPicture, fileRepository->getProcessedPath(), newPictureName, error);
      string originalFullPath = fileRepository->movePicture(tempFilePath, fileRepository->getOriginalsPath(), newPictureName);

      // Update info into storage
      storage->updatePaths(insertedId, originalFullPath, processedFullPath);
      if (error.length() > 0) storage->updateError(insertedId, error);
   }

   delete(storage);
   delete(fileRepository);
}
