cmake_minimum_required(VERSION 3.8)
project(teeko)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp model/Game.cpp model/Game.h model/Space.cpp model/Space.h model/Marker.cpp model/Marker.h model/Player.cpp model/Player.h view/GameRenderer.cpp view/GameRenderer.h view/MainMenu.cpp view/MainMenu.h model/AI.cpp model/AI.h model/Utils.h model/Utils.cpp view/AIMenu.cpp view/AIMenu.h view/Menu.cpp view/Menu.h view/SoundManager.cpp view/SoundManager.h view/SpectatorMenu.cpp view/SpectatorMenu.h)
add_executable(teeko ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(teeko ${SFML_LIBRARIES})
endif()