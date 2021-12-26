#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "../include/global.h"

using namespace cv;

class PictureProcessingInterface {
   public:
      virtual Mat process(Mat pSource) = 0;
   
      typedef PictureProcessingOperation Operation;
      /*enum Operations {
         NO_OPERATION = 0,
         ROTATE_90_LEFT = 1,
         ROTATE_90_RIGHT = 2
      };*/
};
