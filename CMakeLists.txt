cmake_minimum_required(VERSION 3.21)
project(test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(APPLE)
  set(CMAKE_OSX_ARCHITECTURES "arm64" CACHE STRING "" FORCE)
endif()

find_package(Qt6 6.5 COMPONENTS Widgets REQUIRED)
qt_standard_project_setup()

set(SRCS
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

qt_add_executable(test
    MANUAL_FINALIZATION
    MACOSX_BUNDLE
    ${SRCS}
)

target_link_libraries(test PRIVATE Qt6::Widgets)

set_target_properties(test PROPERTIES
    OUTPUT_NAME "test"
    MACOSX_BUNDLE_GUI_IDENTIFIER "com.example.test"
    MACOSX_BUNDLE_BUNDLE_NAME "test"
    MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/Info.plist"
)

install(TARGETS test
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION bin
)

qt_finalize_executable(test)
