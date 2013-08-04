CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(CMAKE_MODULE_PATH $ENV{OPENCV_DIR})

FIND_PACKAGE(OpenCV REQUIRED)

PROJECT(rubiksauto)

#ADD_EXECUTABLE(test test.cpp)

ADD_EXECUTABLE(rubiksauto rubiksauto.cpp extraction.cpp extraction.h image.h contour.h rubiks.h)
TARGET_LINK_LIBRARIES(rubiksauto ${OpenCV_LIBS})
