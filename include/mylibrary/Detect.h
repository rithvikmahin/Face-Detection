#ifndef FACE_DETECT_H
#define FACE_DETECT_H
#include "opencv2/objdetect.hpp"
#include "opencv2/opencv.hpp"
#include "string"

class Detect {
public:
  void OpenVideoStream(std::string feature);
  bool GetIsVideoOpen();
  int GetFacesSize();
  int GetEyesSize();
  int GetMouthSize();
  int GetNoseSize();

  bool LoadFaceCascade(std::string cascade_path);
  bool LoadEyesCascade(std::string cascade_path);
  bool LoadMouthCascade(std::string cascade_path);
  bool LoadNoseCascade(std::string cascade_path);

private:
  bool is_video_open;
  int faces_size;
  int eyes_size;
  int mouth_size;
  int nose_size;

  cv::CascadeClassifier face_cascade;
  cv::CascadeClassifier eyes_cascade;
  cv::CascadeClassifier mouth_cascade;
  cv::CascadeClassifier nose_cascade;

  void DetectEyes(cv::Mat greyscaled_frame, cv::Mat frame,
    std::vector<cv::Rect> faces);
  void DetectMouth(cv::Mat frame, std::vector<cv::Rect> faces);
  void DetectNose(cv::Mat frame, std::vector<cv::Rect> faces);
  void ChooseDetectionFeature(cv::Mat frame, std::string feature);

  cv::Mat DrawFaceBorder(cv::Mat greyscaled_frame, cv::Mat frame,
    std::vector<cv::Rect> faces);
  cv::Mat DrawEyeBorders(cv::Mat greyscaled_frame, cv::Mat frame,
    std::vector<cv::Rect> faces,
    std::vector<cv::Rect> eyes, int face_index);
  cv::Mat DrawMouthBorder(cv::Mat frame, std::vector<cv::Rect> mouth,
    std::vector<cv::Rect> faces, int face_index);
  cv::Mat DrawNoseBorder(cv::Mat frame, std::vector<cv::Rect> nose,
    std::vector<cv::Rect> faces, int face_index);
};

#endif // PROJECT1_DETECT_H