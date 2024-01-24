# Define the sources and headers specific to the _Server library
set(PHAND_SOURCES
    "poker_hand.cc")
set(PHAND_HEADERS
    "poker_hand.h")

# Create the _Client library
add_library(${PHAND} STATIC
    ${PHAND_SOURCES}
    ${PHAND_HEADERS})

# Specify the directories where the compiler should look for include files
target_include_directories(${PHAND} PUBLIC 
    "./"
    "${CMAKE_BINARY_DIR}/configured_files/include"
    # Add any other necessary include directories here
)

# Find the required packages (if these are the same as the other library, you can keep this)
find_package(jsoncpp CONFIG REQUIRED)
find_package(Poco REQUIRED COMPONENTS Foundation Net)

# Link the libraries with the _Server library
target_link_libraries(${PHAND} PRIVATE 
    JsonCpp::JsonCpp
    Poco::Foundation
    Poco::Net
    ${CARD2}
    ${GLOCAL}
)

# Conditional compilation options (same as your other CMake file, adjust if necessary)
if (${ENABLE_WARNINGS})
    target_set_warnings(TARGET ${PHAND} ENABLE ON AS_ERROR OFF)
endif()

if(${ENABLE_LTO})
    target_enable_lto(${PHAND} optimized)
endif()
