cmake_minimum_required(VERSION 3.16)

project(test VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(APPLE)
  set(CMAKE_OSX_ARCHITECTURES "arm64" CACHE STRING "" FORCE)
endif()

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

qt_add_executable(test
        MANUAL_FINALIZATION
        MACOSX_BUNDLE
        ${PROJECT_SOURCES}
)

target_link_libraries(test PRIVATE Qt6::Widgets)

set_target_properties(test PROPERTIES
    OUTPUT_NAME "test"
    MACOSX_BUNDLE_GUI_IDENTIFIER "com.example.test"
    MACOSX_BUNDLE_BUNDLE_NAME "test"    
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS test
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_finalize_executable(test)
