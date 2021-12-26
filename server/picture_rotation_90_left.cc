#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "../include/global.h"
#include "picture_processing_interface.h"
#include "picture_rotation_90_left.h"

using namespace cv;

Mat PictureRotation90Left::process(Mat imgSource) {
   Mat imgResult;
   rotate(imgSource, imgResult, ROTATE_90_COUNTERCLOCKWISE);
   return imgResult;
}
