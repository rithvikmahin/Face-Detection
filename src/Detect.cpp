#include "Detect.h"
#include "opencv2/objdetect.hpp"
#include "opencv2/opencv.hpp"

void Detect::LoadCascades() {
  std::string face_cascade_path = "../../haarcascades/haarcascade_frontalface_alt2.xml";
  if (!face_cascade.load(face_cascade_path)) {
    std::cout << "Could not find the haarcascade! Please place the 'haarcascade_frontalface_alt2.xml' file in the haarcascades folder." << std::endl;
    return;
  }
}

void Detect::OpenVideoStream() {
  cv::Mat frame;
  cv::VideoCapture video;
  //Lowering the buffer size allows the frames to be caught sooner, reducing the lag of the video stream.
  const int buffer_size = 2;
  video.set(cv::CAP_PROP_BUFFERSIZE, buffer_size);
  //0 is the default webcam device, change it for other webcams.
  const int device_id = 0;
  video.open(device_id);

  while (video.read(frame)) {
    DetectFace(frame);
    //The time the video stream waits before registering the pressed key.
    const int delay = 5;
    //The numerical values of the valid character(s) which can interrupt and end the video stream.
    const int end_stream = 0;
    if (cv::waitKey(delay) >= end_stream) {
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
    imshow("Capture - Face detection", frame);
}