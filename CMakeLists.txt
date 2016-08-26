cmake_minimum_required(VERSION 2.8)

project(ImageProcessing)
find_package(OpenCV REQUIRED)
set(raspicam_DIR "/usr/local/lib/cmake")
find_package(raspicam REQUIRED)

include_directories("/usr/local/include/raspicam")

add_executable(ImageApp cameraEdgePi.cpp)
target_link_libraries(ImageApp ${OpenCV_LIBS} ${raspicam_CV_LIBS})
install(TARGETS ImageApp DESTINATION /bin)
