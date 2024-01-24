# Define the sources and headers specific to the _Server library
set(CARD2_SOURCES
    "card2.cc")
set(CARD2_HEADERS
    "card2.h")

# Create the _Client library
add_library(${CARD2} STATIC
    ${CARD2_SOURCES}
    ${CARD2_HEADERS})

# Specify the directories where the compiler should look for include files
target_include_directories(${CARD2} PUBLIC 
    "./"
    "${CMAKE_BINARY_DIR}/configured_files/include"
    # Add any other necessary include directories here
)

# Find the required packages (if these are the same as the other library, you can keep this)
find_package(jsoncpp CONFIG REQUIRED)
find_package(Poco REQUIRED COMPONENTS Foundation Net)

# Link the libraries with the _Server library
target_link_libraries(${CARD2} PRIVATE 
    JsonCpp::JsonCpp
    Poco::Foundation
    Poco::Net
)

# Conditional compilation options (same as your other CMake file, adjust if necessary)
if (${ENABLE_WARNINGS})
    target_set_warnings(TARGET ${CARD2} ENABLE ON AS_ERROR OFF)
endif()

if(${ENABLE_LTO})
    target_enable_lto(${CARD2} optimized)
endif()
