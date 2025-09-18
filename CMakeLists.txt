cmake_minimum_required(VERSION 3.15)

project(py_chiaki_ng 
    VERSION 0.1.0
    DESCRIPTION "Python bindings for chiaki-ng PlayStation Remote Play"
    LANGUAGES CXX C
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(pybind11 REQUIRED)

# Find system dependencies
find_package(PkgConfig REQUIRED)

# Find FFmpeg components
pkg_check_modules(LIBAVCODEC REQUIRED libavcodec)
pkg_check_modules(LIBAVFORMAT REQUIRED libavformat)
pkg_check_modules(LIBAVUTIL REQUIRED libavutil)
pkg_check_modules(LIBSWSCALE REQUIRED libswscale)

# Find OpenSSL
find_package(OpenSSL REQUIRED)

# Find Protobuf
find_package(Protobuf REQUIRED)

# Add chiaki-ng as subdirectory
# We'll configure chiaki-ng to build as a static library
set(CHIAKI_ENABLE_CLI OFF CACHE BOOL "Disable chiaki CLI")
set(CHIAKI_ENABLE_GUI OFF CACHE BOOL "Disable chiaki GUI") 
set(CHIAKI_ENABLE_ANDROID OFF CACHE BOOL "Disable Android build")
set(CHIAKI_ENABLE_STEAM_SHORTCUT OFF CACHE BOOL "Disable Steam shortcuts")
set(CHIAKI_ENABLE_STEAMDECK_NATIVE OFF CACHE BOOL "Disable SteamDeck native")

add_subdirectory(external/chiaki-ng)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/external/chiaki-ng/lib/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${LIBAVCODEC_INCLUDE_DIRS}
    ${LIBAVFORMAT_INCLUDE_DIRS}
    ${LIBAVUTIL_INCLUDE_DIRS}
    ${LIBSWSCALE_INCLUDE_DIRS}
)

# Source files for Python bindings
set(BINDING_SOURCES
    src/py_chiaki_ng.cpp
    src/session_binding.cpp
    src/controller_binding.cpp
    src/video_binding.cpp
    src/events_binding.cpp
)

# Create Python module
pybind11_add_module(py_chiaki_ng_core ${BINDING_SOURCES})

# Link libraries
target_link_libraries(py_chiaki_ng_core PRIVATE
    chiaki-lib
    ${LIBAVCODEC_LIBRARIES}
    ${LIBAVFORMAT_LIBRARIES}
    ${LIBAVUTIL_LIBRARIES}
    ${LIBSWSCALE_LIBRARIES}
    OpenSSL::SSL
    OpenSSL::Crypto
    ${Protobuf_LIBRARIES}
)

# Compiler-specific options
target_compile_definitions(py_chiaki_ng_core PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})

# Set properties
set_target_properties(py_chiaki_ng_core PROPERTIES
    CXX_VISIBILITY_PRESET "hidden"
    VISIBILITY_INLINES_HIDDEN YES
)

# Platform-specific linking
if(UNIX AND NOT APPLE)
    target_link_libraries(py_chiaki_ng_core PRIVATE pthread)
endif()

if(WIN32)
    target_link_libraries(py_chiaki_ng_core PRIVATE ws2_32 iphlpapi)
endif()

# Installation
install(TARGETS py_chiaki_ng_core DESTINATION .)
