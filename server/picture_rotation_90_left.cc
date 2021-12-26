#include "picture_processing_interface.h"
#include "picture_rotation_90_left.h"

Mat PictureRotation90Left::process(Mat imgSource) {
   Mat imgResult;
   rotate(imgSource, imgResult, ROTATE_90_COUNTERCLOCKWISE);
   return imgResult;
}
