cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(test VERSION 1.0.0)

include_directories(
    libraries/json/include
)

add_library(${PROJECT_NAME} SHARED
    src/main.cpp
    src/DeveloperNode.cpp 
    src/DevelopersPopup.cpp
    src/SocialNetworkButton.cpp
    src/DevelopersPageManager.cpp
    src/ErrorsManager/ErrorsManager.cpp
    src/ErrorsManager/ErrorsPopup.cpp
)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

setup_geode_mod(${PROJECT_NAME})
