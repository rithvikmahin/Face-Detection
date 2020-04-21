#ifndef FACE_DETECT_H
#define FACE_DETECT_H
#include "opencv2/objdetect.hpp"

#include <string>

class Detect {
  public:
	  void LoadCascades();
    void VideoStream();
	private:
    cv::CascadeClassifier face_cascade;
};


#endif  // PROJECT1_DETECT_H