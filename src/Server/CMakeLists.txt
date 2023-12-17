# Define the sources and headers specific to the _Server library
set(SERVER_SOURCES
    "server.cc")
set(SERVER_HEADERS
    "server.h")

# Create the _Server library
add_library(${SERVER} STATIC
    ${SERVER_SOURCES}
    ${SERVER_HEADERS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/Database)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/Server)
# Specify the directories where the compiler should look for include files
target_include_directories(${SERVER} PUBLIC 
    "./"
    "${CMAKE_BINARY_DIR}/configured_files/include"
    # Add any other necessary include directories here
)

# Find the required packages (if these are the same as the other library, you can keep this)
find_package(jsoncpp CONFIG REQUIRED)
find_package(Poco REQUIRED COMPONENTS Foundation Net)

# Link the libraries with the _Server library
target_link_libraries(${SERVER} PRIVATE 
    JsonCpp::JsonCpp
    Poco::Foundation
    Poco::Net
    ${SPTT}
)

# Conditional compilation options (same as your other CMake file, adjust if necessary)
if (${ENABLE_WARNINGS})
    target_set_warnings(TARGET ${SERVER} ENABLE ON AS_ERROR OFF)
endif()

if(${ENABLE_LTO})
    target_enable_lto(${SERVER} optimized)
endif()
