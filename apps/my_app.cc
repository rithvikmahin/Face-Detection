// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "Detect.h"
#include "cinder/CinderImGui.h"

namespace myapp {

using cinder::app::KeyEvent;
const int kWindowSize = 500;
const int kButtonSize = 120;
Detect detect;

MyApp::MyApp() { }

void MyApp::setup() {
  ImGui::Initialize();
  cinder::app::setWindowSize(kWindowSize, kWindowSize);
  detect.LoadCascades();
}

void MyApp::update() {
  
  ImGui::SetNextWindowSize(ImVec2(kWindowSize, kWindowSize));
  ImGui::Begin("Detection Options");
  ImGui::Text("Choose a feature to detect.");

  if (ImGui::Button("Face Detection", ImVec2(kButtonSize, kButtonSize))) {
    detect.OpenVideoStream("Face");
  }

  if (ImGui::Button("Eye Detection", ImVec2(kButtonSize, kButtonSize))) {
    detect.OpenVideoStream("Eyes");
  }

  if (ImGui::Button("Nose Detection", ImVec2(kButtonSize, kButtonSize))) {
    detect.OpenVideoStream("Nose");
  }

  if (ImGui::Button("Mouth Detection", ImVec2(kButtonSize, kButtonSize))) {
    detect.OpenVideoStream("Mouth");
  }

  ImGui::End();
}

void MyApp::draw() {

}

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
