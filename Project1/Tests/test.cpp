#include "pch.h"
#include <cinder/Rand.h>
#include "../include/mylibrary/Detect.h"

//Tests if the haarcascade files are being loaded by the function.
//Returns true if the function is able to find and load the file in the provided path, and false otherwise.
TEST(Detect, LoadCascades) {
  Detect detect;
  detect.LoadCascades();
  std::string face_cascade_path = "../../../haarcascades/haarcascade_frontalface_alt2.xml";
  std::string eyes_cascade_path = "../../../haarcascades/haarcascade_eye_tree_eyeglasses.xml";
  cv::CascadeClassifier face_cascade = detect.GetFaceCascade();
  cv::CascadeClassifier eyes_cascade = detect.GetEyesCascade();
  ASSERT_TRUE(face_cascade.load(face_cascade_path));
  ASSERT_TRUE(eyes_cascade.load(eyes_cascade_path));
}
//Tests if the webcam is able to be loaded into a video stream by the function.
//Returns true if a video stream is successfully loaded using the webcam, and false otherwise.
TEST(Detect, OpenVideoStream) {
  Detect detect;
  detect.OpenVideoStream("No parameter");
  bool isVideoOpen = detect.GetIsVideoOpen();
  ASSERT_TRUE(isVideoOpen);
}