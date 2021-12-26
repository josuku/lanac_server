using namespace cv;

class PictureRotation90Left : public PictureProcessingInterface {
   public:
      Mat process(Mat imgSource);
};
