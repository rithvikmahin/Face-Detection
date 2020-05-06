# Face Detection 

Information
---
This C++ project is able to detect and display borders around key facial features in a real-time video stream. These features include the face, eyes, nose and mouth for now.

Dependencies
---
- MSVC 2019
- OpenCV 4.3.0 dev
- Windows 10
- Cinder 0.9.3

Building OpenCV
---
- To use this project, OpenCV 4.3.0 dev must be built from the source for the Visual Studio 2019 compiler. Instructions on how to do that can be found here - https://www.youtube.com/watch?v=M-VHaLHC4XI. The same process can be used for Visual Studio 2019, as the video is for Visual Studio 2017.
- The file opencv_world430d.dll should be moved to the same directory as the .exe for the project.

Building the project in Visual Studio 2019
---
- The following must be added under the properties menu of the FaceDetect solution to run it.
    - Under C++/General, the filepaths to the OpenCV include, test include, project include and Cinder includes should added.
    - Under Linker/General, the filepaths to bin and lib directories in OpenCV along with the Cinder lib directories of x64 and x64/Debug/$(Visual Studio 2019 Version) should be added.
    - Under Linker/Input, the filenames cinder.lib, opencv_world430d.dll and OpenGL32.lib should be added. If the previous instructions were followed, the linker filepaths contain these files in their directories.
- Cinder must be built under the x64 Debug options, in MDd mode under C++/Code Generation in the Runtime Library section.
- Once these have been finished, the project should be able to build and run.

Usage
---
- To use the app, simply click on the button of the feature to detect. A screen will appear, along with the boundaries of the detected features in  real time.
- To exit the detection functionality, press 'q' on the keyboard and close the window. Then, another option can be chosen or the application can be exited.