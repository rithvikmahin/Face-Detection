#ifndef FACE_DETECT_H
#define FACE_DETECT_H
#include "opencv2/objdetect.hpp"

#include <string>

class Detect {
  public:
	  void LoadCascades();
    void OpenVideoStream(std::string feature);
    cv::CascadeClassifier GetFaceCascade();
    cv::CascadeClassifier GetEyesCascade();
	private:
    cv::CascadeClassifier face_cascade;
    cv::CascadeClassifier eyes_cascade;
    void DetectFace(cv::Mat frame);
    void DetectEyes(cv::Mat frame);
};


#endif  // PROJECT1_DETECT_H