cmake_minimum_required(VERSION 3.21)
project(MyQtApp LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Widgets)

add_executable(MyQtApp MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

target_link_libraries(MyQtApp PRIVATE Qt6::Widgets)

set_target_properties(MyQtApp PROPERTIES
  MACOSX_BUNDLE_GUI_IDENTIFIER com.example.myqtapp
  MACOSX_BUNDLE_BUNDLE_NAME "MyQtApp"
)
