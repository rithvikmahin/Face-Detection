#include "Detect.h"
#include "opencv2/objdetect.hpp"
#include "opencv2/opencv.hpp"

// Loads the face haarcascade.
//@param cascade_path - The string of the path to the face haarcascade.
bool Detect::LoadFaceCascade(std::string cascade_path) {
  if (!face_cascade.load(cascade_path)) {
    return false;
  }
  return true;
}

// Loads the eyes haarcascade.
//@param cascade_path - The string of the path to the eyes haarcascade.
bool Detect::LoadEyesCascade(std::string cascade_path) {
  if (!eyes_cascade.load(cascade_path)) {
    return false;
  }
  return true;
}

// Loads the mouth haarcascade.
//@param cascade_path - The string of the path to the mouth haarcascade.
bool Detect::LoadMouthCascade(std::string cascade_path) {
  if (!mouth_cascade.load(cascade_path)) {
    return false;
  }
  return true;
}

// Loads the nose haarcascade.
//@param cascade_path - The string of the path to the nose haarcascade.
bool Detect::LoadNoseCascade(std::string cascade_path) {
  if (!nose_cascade.load(cascade_path)) {
    return false;
  }
  return true;
}

// Creates a window with a video stream.
//@param feature - The string of the feature to be detected.
void Detect::OpenVideoStream(std::string feature) {
  cv::Mat frame;
  cv::VideoCapture video;
  // Lowering the buffer size allows the frames to be caught sooner,
  // reducing the lag of the video stream.
  const int buffer_size = 2;
  video.set(cv::CAP_PROP_BUFFERSIZE, buffer_size);
  // 0 is the default webcam device, change it for other webcams.
  const int device_id = 0;
  video.open(device_id);

  if (video.isOpened()) {
    is_video_open = true;
  }
  else {
    is_video_open = false;
  }

  if (feature == "No parameter") {
    return;
  }

  while (video.read(frame)) {
    ChooseDetectionFeature(frame, feature);
    // The time the video stream waits before registering the pressed key.
    const int delay = 5;
    // The numerical values of the valid character(s) which can interrupt and
    // end the video stream.
    const int end_stream = 0;
    if (cv::waitKey(delay) >= end_stream) {
      video.release();
      break;
    }
  }
}

// A getter for the boolean variable that checks if the video stream is open.
bool Detect::GetIsVideoOpen() { return is_video_open; }

// A getter for the size of the faces array, 0 if no faces are found.
int Detect::GetFacesSize() { return faces_size; }

// A getter for the size of the eyes array, 0 if no eyes are found.
int Detect::GetEyesSize() { return eyes_size; }

// A getter for the size of the mouth array, 0 if no mouth is found.
int Detect::GetMouthSize() { return mouth_size; }

// A getter for the size of the nose array, 0 if no nose is found.
int Detect::GetNoseSize() { return nose_size; }

// Decides which detection function to run.
//@param frame - The current frame taken from the video stream.
//@param feature - The string of the feature to be detected.
void Detect::ChooseDetectionFeature(cv::Mat frame, std::string feature) {
  cv::Mat greyscaled_frame;
  // Converts the 3 channels of the RGB image to 2 channels for the grey version
  // of the same image.
  cvtColor(frame, greyscaled_frame, cv::COLOR_BGR2GRAY);

  std::vector<cv::Rect> faces;
  // The accuracy scale factor, increasing it yields faster detection results at
  // the cost of reduced accuracy.
  const float accuracy = 1.05;
  // The minimum size for the given face, increasing the values leads to an
  // improved frame rate at the cost of reduced accuracy.
  cv::Size size = cv::Size(100, 100);
  // Number of neighbor images from the training model that are considered.
  int neighbors = 3;
  // Number of new haarcascades being used.
  int new_cascades = 0;

  if (feature == "Face") {
    // Identifies the features contained in the provided face haarcascade.
    face_cascade.detectMultiScale(greyscaled_frame, faces, accuracy, neighbors,
      new_cascades | cv::CASCADE_SCALE_IMAGE, size);
    faces_size = faces.size();
    frame = DrawFaceBorder(greyscaled_frame, frame, faces);
    imshow("Face Detection", frame);
  }
  else if (feature == "Eyes") {
    // Identifies the features contained in the provided face haarcascade.
    face_cascade.detectMultiScale(greyscaled_frame, faces, accuracy, neighbors,
      new_cascades | cv::CASCADE_SCALE_IMAGE, size);
    DetectEyes(greyscaled_frame, frame, faces);
  }
  else if (feature == "Mouth") {
    // Identifies the features contained in the provided face haarcascade.
    face_cascade.detectMultiScale(greyscaled_frame, faces, accuracy, neighbors,
      new_cascades | cv::CASCADE_SCALE_IMAGE, size);
    DetectMouth(frame, faces);
  }
  else if (feature == "Nose") {
    // Identifies the features contained in the provided face haarcascade.
    face_cascade.detectMultiScale(greyscaled_frame, faces, accuracy, neighbors,
      new_cascades | cv::CASCADE_SCALE_IMAGE, size);
    DetectNose(frame, faces);
  }
  else {
    return;
  }
}

// Predicts the location of the mouth from the frame.
//@param frame - The current frame taken from the video stream.
//@param faces - A vector of OpenCV rectangles holding the face snapshots from
//the frame.
//@param face_index - The current face snapshot's index.
void Detect::DetectMouth(cv::Mat frame, std::vector<cv::Rect> faces) {
  for (int face_index = 0; face_index < faces.size(); face_index++) {
    cv::Mat face_frame = frame(faces[face_index]);
    // Converts the 3 channel RBG frame to a 2 channel grey frame.
    cvtColor(face_frame, face_frame, cv::COLOR_BGR2GRAY);
    std::vector<cv::Rect> mouth;
    // Compares against the haarcascade to make a prediction.
    mouth_cascade.detectMultiScale(face_frame, mouth);
    mouth_size = mouth.size();
    DrawMouthBorder(frame, mouth, faces, face_index);
  }
  imshow("output", frame);
}

// Draws the physical grid around the location of the mouth with extra space.
//@param frame - The current frame taken from the video stream.
//@param faces - A vector of OpenCV rectangles holding the face snapshots from
//the frame.
//@param mouth - A vector of OpenCV rectangles holding the mouth snapshots from
//the frame.
cv::Mat Detect::DrawMouthBorder(cv::Mat frame, std::vector<cv::Rect> mouth,
  std::vector<cv::Rect> faces, int face_index) {
  for (int mouth_index = 0; mouth_index < mouth.size(); mouth_index++) {
    const float start_of_mouth_horizontal = mouth[0].x;
    const float start_of_face_horizontal = faces[face_index].x;
    const float start_of_mouth_vertical = mouth[0].y;
    const float start_of_face_vertical = faces[face_index].y;
    // A point representing the upper-left starting vertex of the mouth.
    cv::Point mouth_vertex_top(
      start_of_mouth_horizontal + start_of_face_horizontal,
      start_of_mouth_vertical + start_of_face_vertical);

    const float mouth_width = mouth[0].width;
    const float mouth_height = mouth[0].height;
    const float rectangle_length = mouth_vertex_top.x + mouth_width;
    const float rectangle_height = mouth_vertex_top.y + mouth_height;
    // The RGB value for the color of the rectangle.
    cv::Scalar color = cv::Scalar(255, 255, 0);
    // A point representing the bottom right vertex of the mouth.
    cv::Point mouth_vertex_bottom(rectangle_length, rectangle_height);
    int thickness = 4;
    // The predefined type of line provided by OpenCV.
    int line_type = 8;
    // The clarity of the border.
    int shift = 0;
    rectangle(frame, mouth_vertex_top, mouth_vertex_bottom, color, thickness,
      line_type, shift);
  }
  return frame;
}

// Draws the physical grid around the location of the face with extra space.
//@param greyscaled_frame - The greyed 2 channel version of the current frame
//from the video stream.
//@param frame - The current frame taken from the video stream.
//@param feature - The string of the feature to be detected.
cv::Mat Detect::DrawFaceBorder(cv::Mat greyscaled_frame, cv::Mat frame,
  std::vector<cv::Rect> faces) {
  for (int face_index = 0; face_index < faces.size(); face_index++) {
    // The leftmost point of the face.
    const float start_of_face_horizontal = faces[face_index].x;
    const float face_horizontal_center = faces[face_index].width / 2;
    // The highest point of the face.
    const float start_of_face_vertical = faces[face_index].y;
    const float face_vertical_center = faces[face_index].height / 2;

    cv::Point center(start_of_face_horizontal + face_horizontal_center,
      start_of_face_vertical + face_vertical_center);
    // The RGB value of the ellipse to be drawn.
    cv::Scalar color = cv::Scalar(255, 0, 255);
    // The size of the axes of the ellipse.
    cv::Size axes = cv::Size(face_horizontal_center, face_vertical_center);
    // The initial tilt of the ellipse.
    int initial_angle = 0;
    // The final tilt of the ellipse's arc.
    int final_angle = 360;
    // The clarity of the border, set to 4 as the pixels distort due to the
    // semi-circular shape.
    int shift = 4;
    // Draws an ellipse around the detected face.
    ellipse(frame, center, axes, initial_angle, initial_angle, final_angle,
      color, shift);
  }
  return frame;
}

// Predicts the location of the eyes from the frame.
//@param greyscaled_frame - The greyed 2 channel version of the current frame
//from the video stream.
//@param frame - The current frame taken from the video stream.
//@param faces - A vector of OpenCV rectangles holding the face snapshots from
//the frame.
void Detect::DetectEyes(cv::Mat greyscaled_frame, cv::Mat frame,
  std::vector<cv::Rect> faces) {
  for (int face_index = 0; face_index < faces.size(); face_index++) {
    cv::Mat face_frame = greyscaled_frame(faces[face_index]);
    std::vector<cv::Rect> eyes;
    // Identifies and tracks the eye based on the features contained in the
    // haarcascade.
    eyes_cascade.detectMultiScale(face_frame, eyes);
    eyes_size = eyes.size();
    DrawEyeBorders(greyscaled_frame, frame, faces, eyes, face_index);
  }
  imshow("Eye Detection", frame);
}

// Draws the physical grid around the location of the eyes with extra space.
//@param greyscaled_frame - The greyed 2 channel version of the current frame
//from the video stream.
//@param frame - The current frame taken from the video stream.
//@param faces - A vector of OpenCV rectangles holding the face snapshots from
//the frame.
//@param eyes - A vector of OpenCV rectangles holding the eye snapshots from the
//frame.
//@param face_index - The current face snapshot's index.
cv::Mat Detect::DrawEyeBorders(cv::Mat greyscaled_frame, cv::Mat frame,
  std::vector<cv::Rect> faces,
  std::vector<cv::Rect> eyes, int face_index) {
  for (int eye_index = 0; eye_index < eyes.size(); eye_index++) {
    const float eye_width = eyes[eye_index].width;
    const float eye_height = eyes[eye_index].height;
    // The leftmost point of the face.
    const float start_of_face_horizontal = faces[face_index].x;
    // The leftmost point of the eye.
    const float start_of_eye_horizontal = eyes[eye_index].x;
    const float eye_center_horizontal = eye_width / 2;
    // The highest point of the face.
    const float start_of_face_vertical = faces[face_index].y;
    // The highest point of the eye.
    const float start_of_eye_vertical = eyes[eye_index].y;
    const float eye_center_vertical = eye_height / 2;

    cv::Point eye_center(start_of_face_horizontal + start_of_eye_horizontal +
      eye_center_horizontal,
      start_of_face_vertical + start_of_eye_vertical +
      eye_center_vertical);
    int circle_radius = cvRound((eye_height + eye_width) / 4);
    // The RGB value of the circle to be drawn.
    cv::Scalar color = cv::Scalar(255, 0, 0);
    int thickness = 4;
    circle(frame, eye_center, circle_radius, color, thickness);
  }
  return frame;
}

// Predicts the location of the nose from the frame.
//@param frame - The current frame taken from the video stream.
//@param faces - A vector of OpenCV rectangles holding the face snapshots from
//the frame.
void Detect::DetectNose(cv::Mat frame, std::vector<cv::Rect> faces) {
  for (int face_index = 0; face_index < faces.size(); face_index++) {
    cv::Mat face_frame = frame(faces[face_index]);
    std::vector<cv::Rect> nose;
    // Turns the 3 channel RGB frame into a 2 channel grey frame.
    cvtColor(face_frame, face_frame, cv::COLOR_BGR2GRAY);
    // Uses the nose haarcascade to detect features of the nose.
    nose_cascade.detectMultiScale(face_frame, nose);
    nose_size = nose.size();
    DrawNoseBorder(frame, nose, faces, face_index);
  }
  imshow("output", frame);
}

// Draws the physical grid around the location of the nose with extra space.
//@param frame - The current frame taken from the video stream.
//@param nose - A vector of OpenCV rectangles holding the nose snapshots from
//the frame.
//@param faces - A vector of OpenCV rectangles holding the face snapshots from
//the frame.
//@param face_index - The current face snapshot's index.
cv::Mat Detect::DrawNoseBorder(cv::Mat frame, std::vector<cv::Rect> nose,
  std::vector<cv::Rect> faces, int face_index) {
  for (int nose_index = 0; nose_index < nose.size(); nose_index++) {
    const float nose_width = nose[0].width;
    const float nose_height = nose[0].height;

    const float start_of_nose_horizontal = nose[0].x;
    const float start_of_nose_vertical = nose[0].y;
    const float start_of_face_horizontal = faces[face_index].x;
    const float start_of_face_vertical = faces[face_index].y;
    // A point representing the upper-left corner of the nose.
    cv::Point nose_corner_top(start_of_nose_horizontal +
      start_of_face_horizontal,
      start_of_nose_vertical + start_of_face_vertical);

    const float rectangle_length = nose_corner_top.x + nose_width;
    const float rectangle_height = nose_corner_top.y + nose_height;
    // A point representing the bottom-right corner of the nose.
    cv::Point nose_corner_bottom(rectangle_length, rectangle_height);
    // The RGB value for the color of the rectangle.
    cv::Scalar color = cv::Scalar(255, 255, 255);
    int thickness = 4;
    // The predefined line type for OpenCV's rectangle.
    int line_type = 7;
    // The clarity of the border.
    int shift = 0;
    rectangle(frame, nose_corner_top, nose_corner_bottom, color, thickness,
      line_type, shift);
  }
  return frame;
}