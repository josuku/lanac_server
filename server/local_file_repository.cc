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

LocalFileRepository::LocalFileRepository(string path)
{
   this->filePath = path;
}

LocalFileRepository::~LocalFileRepository() 
{

}

string LocalFileRepository::getTempPath()
{
   string path = filePath + "temp/";
   cv::utils::fs::createDirectory(path);
   return path;
}

string LocalFileRepository::getOriginalsPath()
{
   string path = filePath + "original/";
   cv::utils::fs::createDirectory(path);
   return path;
}

string LocalFileRepository::getProcessedPath()
{
   string path = filePath + "processed/";
   cv::utils::fs::createDirectory(path);
   return path;
}

string LocalFileRepository::savePicture(Mat picture, string fullpath, string &error)
{
   try 
   {
      imwrite(fullpath, picture);
      return fullpath;
   }
   catch (exception& e)
   {
      error = e.what();
      cout << "[Server] ERROR: Error saving picture in " << fullpath << ": " << error << endl;
      return "";
   }
}

string LocalFileRepository::savePicture(Mat picture, string path, string filename, string &error) 
{
   string fullPath;
   try 
   {
      fullPath = path + filename;
      imwrite(fullPath, picture);
      return fullPath;
   }
   catch (exception& e)
   {
      error = e.what();
      cout << "[Server] ERROR: Error saving picture in " << fullPath << ": " << error << endl;
      return "";
   }
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
