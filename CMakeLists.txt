cmake_minimum_required(VERSION 3.8)
project(teeko)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp Game.cpp Game.h Board.cpp Board.h Space.cpp Space.h Marker.cpp Marker.h)
add_executable(teeko ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(teeko ${SFML_LIBRARIES})
endif()