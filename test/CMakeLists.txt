cmake_minimum_required(VERSION 3.10)
project(Poker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/test/Client)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/test/Database)

add_executable(PokerClient test/client/client.cc test/Database/Creationaccount.cpp)

target_link_libraries(PokerClient sqlite3)
