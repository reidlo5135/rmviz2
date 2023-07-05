cmake_minimum_required(VERSION 3.5)

project(rmviz2 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
  include
  include/${PROJECT_NAME}
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(rmviz2
  src/main.cpp
  src/window/mainwindow.cpp
  include/mainwindow.h
  src/window/mainwindow.ui
)

target_link_libraries(rmviz2 PRIVATE Qt5::Widgets)