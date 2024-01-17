# Define the sources and headers specific to the _Server library
set(PTSTATE_SOURCES
    "poker_table_state.cc")
set(PTSTATE_HEADERS
    "poker_table_state.h")

# Create the _Server library
add_library(${PTSTATE} STATIC
    ${PTSTATE_SOURCES}
    ${PTSTATE_HEADERS})

# Specify the directories where the compiler should look for include files
target_include_directories(${PTSTATE} PUBLIC 
    "./"
    "${CMAKE_BINARY_DIR}/configured_files/include"
    # Add any other necessary include directories here
)

# Find the required packages (if these are the same as the other library, you can keep this)
find_package(jsoncpp CONFIG REQUIRED)
find_package(Poco REQUIRED COMPONENTS Foundation Net)

# Link the libraries with the _Server library
target_link_libraries(${PTSTATE} PRIVATE 
    JsonCpp::JsonCpp
    Poco::Foundation
    Poco::Net
    ${SPTT}
    ${DEALER}
    ${CARD}
)

# Conditional compilation options (same as your other CMake file, adjust if necessary)
if (${ENABLE_WARNINGS})
    target_set_warnings(TARGET ${PTSTATE} ENABLE ON AS_ERROR OFF)
endif()

if(${ENABLE_LTO})
    target_enable_lto(${PTSTATE} optimized)
endif()
