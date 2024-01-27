project(Bots)

cmake_minimum_required(VERSION 3.10)
project(YourProjectName)

# Find the QtWidgets library
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Tell CMake to run moc, uic, and rcc when necessary
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Source files
set(SOURCES main.cpp MainWindow.cpp)

# Headers
set(HEADERS MainWindow.h)

# Create the executable
add_executable(YourProjectName ${SOURCES} ${HEADERS})

# Link with Qt libraries
target_link_libraries(YourProjectName Qt5::Widgets)

# Collect source files in this folder and all subfolders
file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADERS "*.hpp")

# Create a library or executable with these files
# For a library: add_library(Bots STATIC ${SOURCES} ${HEADERS})
# For an executable: add_executable(Bots ${SOURCES} ${HEADERS})

# Include the current directory
target_include_directories(Bots PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})