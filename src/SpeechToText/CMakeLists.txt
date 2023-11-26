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

if (${ENABLE_WARNINGS})
    target_set_warnings(TARGET ${SPTT} ENABLE ON AS_ERROR OFF)
endif()

if(${ENABLE_LTO})
    target_enable_lto(${SPTT} optimized)
endif()