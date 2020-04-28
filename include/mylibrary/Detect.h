#ifndef FACE_DETECT_H
#define FACE_DETECT_H
#include "opencv2/objdetect.hpp"

#include <string>

class Detect {
  public:
	  void LoadCascades();
    void OpenVideoStream();
	private:
    cv::CascadeClassifier face_cascade;
    void DetectFace(cv::Mat frame);
};


#endif  // PROJECT1_DETECT_H