include(GNUInstallDirs)

# If no build type was specified, set it to Release.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING
            "Choose the type of build, options are: None Debug Release."
            FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# If no installation prefix is given manually, install locally.
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE STRING
            "The install location"
            FORCE)
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

set(EXE_SOURCES
    "main.cpp")
 
add_compile_definitions(CMAKE_SOURCE_DIR="${CMAKE_SOURCE_DIR}")
message("Build type: " ${CMAKE_BUILD_TYPE})
if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_definitions(DEBUG)
    add_compile_definitions(MODE_CLI=1)
else(CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_definitions(MODE_CLI=0)
endif(CMAKE_BUILD_TYPE MATCHES Debug)
    
add_executable(${EXECUTABLE} 
    ${EXE_SOURCES})

if (${ENABLE_WARNINGS})
    target_set_warnings(TARGET ${EXECUTABLE} ENABLE ON AS_ERROR OFF)
endif()

find_package(Poco REQUIRED COMPONENTS Foundation Net)

target_link_libraries(${EXECUTABLE} PRIVATE
    ${SPTT}
    ${SERVER}
    Poco::Foundation
    Poco::Net
)