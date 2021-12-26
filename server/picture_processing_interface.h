using namespace cv;

class PictureProcessingInterface {
   public:
      virtual Mat process(Mat pSource) = 0;
   
      typedef PictureProcessingOperation Operation;
};
