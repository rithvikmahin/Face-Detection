// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "Detect.h"
#include "cinder/CinderImGui.h"

namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp() { }

void MyApp::setup() {
  ImGui::Initialize();
  Detect detect;
  detect.LoadCascades();
  detect.OpenVideoStream();
}

void MyApp::update() { }

void MyApp::draw() {
  cinder::gl::clear(cinder::Color(0, 0, 0));
  ImGui::Text("Hello, world!");
}

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
