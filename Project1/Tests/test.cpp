#include "../include/mylibrary/Detect.h"
#include "pch.h"
#include <cinder/Rand.h>

const std::string kFaceCascadePath =
"../../../haarcascades/haarcascade_frontalface_alt2.xml";
const std::string kEyesCascadePath =
"../../../haarcascades/haarcascade_eye_tree_eyeglasses.xml";
const std::string kMouthCascadePath =
"../../../haarcascades/haarcascade_mcs_mouth.xml";
const std::string kNoseCascadePath =
"../../../haarcascades/haarcascade_mcs_nose.xml";

// Tests if the haarcascade file is being loaded by the function.
// Returns true if the function is able to find and load the face haarcascade in
// the provided path, and false otherwise.
TEST(Detect, CanLoadFaceCascade) {
  Detect detect;
  bool face_cascade = detect.LoadFaceCascade(kFaceCascadePath);
  ASSERT_TRUE(face_cascade);
}

// Tests if the haarcascade file is being loaded by the function.
// Returns true if the function is able to find and load the eye haarcascade in
// the provided path, and false otherwise.
TEST(Detect, CanLoadEyesCascade) {
  Detect detect;
  bool eyes_cascade = detect.LoadEyesCascade(kEyesCascadePath);
  ASSERT_TRUE(eyes_cascade);
}

// Tests if the haarcascade file is being loaded by the function.
// Returns true if the function is able to find and load the mouth haarcascade
// in the provided path, and false otherwise.
TEST(Detect, CanLoadMouthCascade) {
  Detect detect;
  bool mouth_cascade = detect.LoadMouthCascade(kMouthCascadePath);
  ASSERT_TRUE(mouth_cascade);
}

// Tests if the haarcascade file is being loaded by the function.
// Returns true if the function is able to find and load the mouth haarcascade
// in the provided path, and false otherwise.
TEST(Detect, CanLoadNoseCascade) {
  Detect detect;
  bool nose_cascade = detect.LoadNoseCascade(kNoseCascadePath);
  ASSERT_TRUE(nose_cascade);
}

// Tests if the haarcascade file is unable to be loaded by the function.
// Returns false if the function is unable to find and load the face haarcascade
// in the provided path, and true otherwise.
TEST(Detect, CannotLoadFaceCascade) {
  Detect detect;
  bool face_cascade = detect.LoadFaceCascade("31");
  ASSERT_FALSE(face_cascade);
}

// Tests if the haarcascade file is unable to be loaded by the function.
// Returns false if the function is unable to find and load the face haarcascade
// in the provided path, and true otherwise.
TEST(Detect, CannotLoadEyesCascade) {
  Detect detect;
  bool eyes_cascade = detect.LoadEyesCascade("blank.xml");
  ASSERT_FALSE(eyes_cascade);
}

// Tests if the haarcascade file is unable to be loaded by the function.
// Returns false if the function is unable to find and load the face haarcascade
// in the provided path, and true otherwise.
TEST(Detect, CannotLoadMouthCascade) {
  Detect detect;
  bool mouth_cascade = detect.LoadNoseCascade("haarcascade_mc_mouth.xml");
  ASSERT_FALSE(mouth_cascade);
}

// Tests if the haarcascade file is unable to be loaded by the function.
// Returns false if the function is unable to find and load the face haarcascade
// in the provided path, and true otherwise.
TEST(Detect, CannotLoadNoseCascade) {
  Detect detect;
  bool nose_cascade = detect.LoadNoseCascade("   ");
  ASSERT_FALSE(nose_cascade);
}

// Tests if the webcam is able to be loaded into a video stream by the function.
// Returns true if a video stream is successfully loaded using the webcam, and
// false otherwise.
TEST(Detect, OpenVideoStream) {
  Detect detect;
  detect.OpenVideoStream("No parameter");
  bool isVideoOpen = detect.GetIsVideoOpen();
  ASSERT_TRUE(isVideoOpen);
}

// Tests if a face was found in the video stream, by checking if the face array
// has at least one face in it. Returns true if the array contains at least one
// element, and false otherwise.
TEST(Detect, FaceDetected) {
  Detect detect;
  detect.OpenVideoStream("Face");
  int faces_size = detect.GetFacesSize();
  ASSERT_TRUE(faces_size > 0);
}

// Tests if an eye was found in the video stream, by checking if the eye array
// has at least one eye in it. Returns true if the array contains at least one
// element, and false otherwise.
TEST(Detect, EyesDetected) {
  Detect detect;
  detect.OpenVideoStream("Eyes");
  int eyes_size = detect.GetEyesSize();
  ASSERT_TRUE(eyes_size > 0);
}

// Tests if a mouth was found in the video stream, by checking if the mouth
// array has at least one mouth in it. Returns true if the array contains at
// least one element, and false otherwise.
TEST(Detect, MouthDetected) {
  Detect detect;
  detect.OpenVideoStream("Mouth");
  int mouth_size = detect.GetMouthSize();
  ASSERT_TRUE(mouth_size > 0);
}

// Tests if a nose was found in the video stream, by checking if the nose array
// has at least one nose in it. Returns true if the array contains at least one
// element, and false otherwise.
TEST(Detect, NoseDetected) {
  Detect detect;
  detect.OpenVideoStream("Nose");
  int nose_size = detect.GetNoseSize();
  ASSERT_TRUE(nose_size > 0);
}