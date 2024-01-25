# Define the sources and headers specific to the _Server library
set(CLIENT_SOURCES
    "client.cc")
set(CLIENT_HEADERS
    "client.h")

# Create the _Client library
add_library(${CLIENT} STATIC
    ${CLIENT_SOURCES}
    ${CLIENT_HEADERS})

# Specify the directories where the compiler should look for include files
target_include_directories(${CLIENT} PUBLIC 
    "./"
    "${CMAKE_BINARY_DIR}/configured_files/include"
    # Add any other necessary include directories here
)

# Find the required packages (if these are the same as the other library, you can keep this)
find_package(jsoncpp CONFIG REQUIRED)
find_package(Poco REQUIRED COMPONENTS Foundation Net)

# Link the libraries with the _Server library
target_link_libraries(${CLIENT} PRIVATE 
    JsonCpp::JsonCpp
    Poco::Foundation
    Poco::Net
    ${PLAYER}
    ${CARD}
)

# Conditional compilation options (same as your other CMake file, adjust if necessary)
if (${ENABLE_WARNINGS})
    target_set_warnings(TARGET ${CLIENT} ENABLE ON AS_ERROR OFF)
endif()

if(${ENABLE_LTO})
    target_enable_lto(${CLIENT} optimized)
endif()
