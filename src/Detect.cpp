#include "Detect.h"
#include "opencv2/objdetect.hpp"
#include "opencv2/opencv.hpp"

void Detect::LoadCascades() {
  face_cascade.load("../../haarcascades/haarcascade_frontalcatface.xml");
}

void Detect::VideoStream() {
  cv::Mat frame;
  cv::VideoCapture video;
  video.open(0);
  while (true) {
    video.read(frame);
    cv::imshow("Current frame", frame);
    if (cv::waitKey(5) >= 0) {
      break;
    }
  }
}