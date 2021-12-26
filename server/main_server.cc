#include "picture_processing_interface.h"
#include "picture_rotation_90_left.h"
#include "picture_rotation_90_right.h"
#include "server.h"

using namespace std;
using namespace cv;

void processPictureChange(PictureProcessingInterface::Operation operation, string originalPicturePath, string pictureName) 
{
   PictureProcessingInterface * pictureOperation = NULL;
   Mat originalPicture, processedPicture;
   originalPicture = imread(originalPicturePath, IMREAD_COLOR);
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
         return;
   }
   processedPicture = pictureOperation->process(originalPicture);
   imwrite(string(SAVE_FOLDER) + pictureName + "_rotated.jpg", processedPicture);
}

// Main function
int main(int argc, char *argv[])
{
   Server server(PORT, MAX_CONNECTIONS);
   if (!server.createServer()) return -1;
   while (true) 
   {
      if (!server.acceptConnection()) return -1;
      FileHeader fileHeader = server.receiveFileHeader();
      if (strlen(fileHeader.name) == 0) return -1;
      string newFilePath = server.receiveFile(fileHeader.name);
      if (newFilePath.length() == 0) return -1;
      
      processPictureChange(fileHeader.operation, newFilePath, fileHeader.name);
   }
}
