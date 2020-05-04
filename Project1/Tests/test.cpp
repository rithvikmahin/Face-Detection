#include "pch.h"
#include <cinder/Rand.h>
#include "../include/mylibrary/Detect.h"


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