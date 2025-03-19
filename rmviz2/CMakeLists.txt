cmake_minimum_required(VERSION 3.8)
project(rmviz2)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(can_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

include_directories(
  include/
  ${Qt5Core_INCLUDE_DIRS}
  ${Qt5Quick_INCLUDE_DIRS}
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(EXEC_NAME ${PROJECT_NAME})

set(SOURCES
  include/ui/mainwindow.hpp
  src/ui/mainwindow.cpp
  src/ui/mainwindow.ui
  src/application/can.cpp
  src/presentation/node.cpp
  src/main.cpp
)

set(DEPENDS
  rclcpp
  can_msgs
  nav_msgs
  sensor_msgs
  geometry_msgs
)

add_executable(${EXEC_NAME}
  ${SOURCES}
)

ament_target_dependencies(${EXEC_NAME}
  ${DEPENDS}
)

target_link_libraries(${EXEC_NAME} Qt${QT_VERSION_MAJOR}::Widgets)

install(TARGETS ${EXEC_NAME}
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()

