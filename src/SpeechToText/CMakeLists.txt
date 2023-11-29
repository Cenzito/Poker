set(SPTT_SOURCES
    "speech_to_text.cc")
set(CUI_HEADERS
    "speech_to_text.h")

add_library(${SPTT} STATIC
    ${SPTT_SOURCES}
    ${SPTT_HEADERS})

target_include_directories(${SPTT} PUBLIC 
    "./"
    "${CMAKE_BINARY_DIR}/configured_files/include"
    julius::julius)

find_package(jsoncpp CONFIG REQUIRED)
find_package(Poco REQUIRED COMPONENTS Foundation Net)                                

target_link_libraries(${SPTT} PRIVATE 
    JsonCpp::JsonCpp
    Poco::Foundation
    Poco::Net
)

if (${ENABLE_WARNINGS})
    target_set_warnings(TARGET ${SPTT} ENABLE ON AS_ERROR OFF)
endif()

if(${ENABLE_LTO})
    target_enable_lto(${SPTT} optimized)
endif()