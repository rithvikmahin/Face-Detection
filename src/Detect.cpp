#include "Detect.h"
#include "opencv2/objdetect.hpp"
#include "opencv2/opencv.hpp"

void Detect::LoadCascades() {
  std::string face_cascade_path = "../../haarcascades/haarcascade_frontalface_alt2.xml";
  std::string eyes_cascade_path = "../../haarcascades/haarcascade_eye_tree_eyeglasses.xml";

  if (!face_cascade.load(face_cascade_path)) {
    std::cout << "Could not find the face haarcascade! Please place the 'haarcascade_frontalface_alt2.xml' file in the haarcascades folder." << std::endl;
    return;
  }

  if (!eyes_cascade.load(eyes_cascade_path)) {
    std::cout << "Could not find the eyes haarcascade! Please place the 'haarcascade_eye_tree_eyeglasses.xml' file in the haarcascades folder." << std::endl;
    return;
  }
}

cv::CascadeClassifier Detect::GetFaceCascade() {
  return face_cascade;
}

cv::CascadeClassifier Detect::GetEyesCascade() {
  return eyes_cascade;
}

void Detect::OpenVideoStream(std::string feature) {
  cv::Mat frame;
  cv::VideoCapture video;
  //Lowering the buffer size allows the frames to be caught sooner, reducing the lag of the video stream.
  const int buffer_size = 2;
  video.set(cv::CAP_PROP_BUFFERSIZE, buffer_size);
  //0 is the default webcam device, change it for other webcams.
  const int device_id = 0;
  video.open(device_id);

  while (video.read(frame)) {
    if (feature == "Face") {
      DetectFace(frame);
    }
    else if (feature == "Eyes") {
      DetectEyes(frame);
    }
    //The time the video stream waits before registering the pressed key.
    const int delay = 5;
    //The numerical values of the valid character(s) which can interrupt and end the video stream.
    const int end_stream = 0;
    if (cv::waitKey(delay) >= end_stream) {
      video.release();
      break;
    }
  }
}

void Detect::DetectFace(cv::Mat frame) {
    cv::Mat greyscaled_frame;
    //Converts the 3 channels of the RGB image to 2 channels for the grey version of the same image.
    cvtColor(frame, greyscaled_frame, cv::COLOR_BGR2GRAY);

    std::vector<cv::Rect> faces;
    //The accuracy scale factor, increasing it yields faster detection results at the cost of reduced accuracy.
    const double accuracy = 1.05;
    //The minimum size for the given face, increasing the values leads to an improved frame rate at the cost of reduced accuracy.
    cv::Size size = cv::Size(100, 100);
    //Identifies the features contained in the provided haarcascades.
    face_cascade.detectMultiScale(greyscaled_frame, faces, accuracy, 3, 0 | cv::CASCADE_SCALE_IMAGE, size);

    for (int face_index = 0; face_index < faces.size(); face_index++) {
      //The leftmost point of the face.
      const double start_of_face_horizontal = faces[face_index].x;
      //The point located horizontally halfway through the face.
      const double face_horizontal_center = faces[face_index].width / 2;
      //The highest point of the face.
      const double start_of_face_vertical = faces[face_index].y;
      //The point located vertically halfway through the face.
      const double face_vertical_center = faces[face_index].height / 2;
      cv::Point center(start_of_face_horizontal + face_horizontal_center, start_of_face_vertical + face_vertical_center);
      //Draws an ellipse around the detected face.
      ellipse(frame, center, cv::Size(face_horizontal_center, face_vertical_center), 0, 0, 360, cv::Scalar(255, 0, 255), 4);
    }
    imshow("Face Detection", frame);
}

void Detect::DetectEyes(cv::Mat frame) {
  cv::Mat greyscaled_frame;
  //Converts the 3 channels of the RGB image to 2 channels for the grey version of the same image.
  cvtColor(frame, greyscaled_frame, cv::COLOR_BGR2GRAY);

  std::vector<cv::Rect> faces;
  //The accuracy scale factor, increasing it yields faster detection results at the cost of reduced accuracy.
  const double accuracy = 1.05;
  //The minimum size for the given face, increasing the values leads to an improved frame rate at the cost of reduced accuracy.
  cv::Size size = cv::Size(100, 100);
  //Identifies the features contained in the provided haarcascades.
  face_cascade.detectMultiScale(greyscaled_frame, faces, accuracy, 3, 0 | cv::CASCADE_SCALE_IMAGE, size);

  for (int face_index = 0; face_index < faces.size(); face_index++) {
    cv::Mat face_frame = greyscaled_frame(faces[face_index]);
    std::vector<cv::Rect> eyes;
    //Identifies and tracks the eye based on the features contained in the haarcascade.
    eyes_cascade.detectMultiScale(face_frame, eyes);

    for (int eye_index = 0; eye_index < eyes.size(); eye_index++) {
      const double eye_width = eyes[eye_index].width;
      const double eye_height = eyes[eye_index].height;
      //The leftmost point of the face.
      const double start_of_face_horizontal = faces[face_index].x;
      //The leftmost point of the eye.
      const double start_of_eye_horizontal = eyes[eye_index].x;
      //The center x-coordinate of the eye.
      const double eye_center_horizontal = eye_width / 2;
      //The highest point of the face.
      const double start_of_face_vertical = faces[face_index].y;
      //The highest point of the eye.
      const double start_of_eye_vertical = eyes[eye_index].y;
      //The center y-coordinate of the eye.
      const double eye_center_vertical = eye_height / 2;
      cv::Point eye_center(start_of_face_horizontal + start_of_eye_horizontal + eye_center_horizontal, 
        start_of_face_vertical + start_of_eye_vertical + eye_center_vertical);
      int circle_radius = cvRound((eye_height + eye_width) / 4);
      circle(frame, eye_center, circle_radius, cv::Scalar(255, 0, 0), 4);
    }
  }
  imshow("Eye Detection", frame);
}