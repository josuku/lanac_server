#include <iostream>
#include <cstdio>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utils/filesystem.hpp>
#include "../include/global.h"
#include "file_repository_interface.h"
#include "local_file_repository.h"

using namespace std;
using namespace cv;

string LocalFileRepository::getTempPath()
{
   string path = SAVE_FOLDER + "temp/";
   cv::utils::fs::createDirectory(path);
   return path;
}

string LocalFileRepository::getOriginalsPath()
{
   string path = SAVE_FOLDER + "original/";
   cv::utils::fs::createDirectory(path);
   return path;
}

string LocalFileRepository::getProcessedPath()
{
   string path = SAVE_FOLDER + "processed/";
   cv::utils::fs::createDirectory(path);
   return path;
}

string LocalFileRepository::savePicture(Mat picture, string fullpath)
{
   imwrite(fullpath, picture);
   return fullpath;
}

string LocalFileRepository::savePicture(Mat picture, string path, string filename) 
{
   string fullPath = path + filename;
   imwrite(fullPath, picture);
   return fullPath;
}

string LocalFileRepository::movePicture(string originalFullPath, string newPath, string filename)
{
   string newFullPath = newPath + filename;
   if (rename(originalFullPath.c_str(), newFullPath.c_str()) < 0)
   {
      cout << "[Server] Error moving picture" << endl;
      return "";
   }
   return newFullPath;
}
