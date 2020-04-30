// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "Detect.h"
#include "cinder/CinderImGui.h"
#include "string"

namespace myapp {

using cinder::app::KeyEvent;
const int window_size = 500;
const int button_size = 120;

MyApp::MyApp() { }

void MyApp::setup() {
  ImGui::Initialize();
  cinder::app::setWindowSize(window_size, window_size);
}

void MyApp::update() {
  Detect detect;
  
  ImGui::SetNextWindowSize(ImVec2(window_size, window_size));
  ImGui::Begin("Options");
  ImGui::Text("Detection Options");

  if (ImGui::Button("Face Detection", ImVec2(button_size, button_size))) {
    detect.LoadCascades();
    detect.OpenVideoStream();
  }

  ImGui::End();
}

void MyApp::draw() {

}

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
