cmake_minimum_required(VERSION 3.21)
project(test LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Widgets)

add_executable(test MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

target_link_libraries(test PRIVATE Qt6::Widgets)

set_target_properties(test PROPERTIES
  MACOSX_BUNDLE_GUI_IDENTIFIER com.example.test
  MACOSX_BUNDLE_BUNDLE_NAME "test"
)
