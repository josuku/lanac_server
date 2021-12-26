#include "picture_processing_interface.h"
#include "picture_rotation_90_right.h"

Mat PictureRotation90Right::process(Mat imgSource) {
   Mat imgResult;
   rotate(imgSource, imgResult, ROTATE_90_CLOCKWISE);
   return imgResult;
}
