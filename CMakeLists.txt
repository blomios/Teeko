cmake_minimum_required(VERSION 3.8)
project(teeko)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/main.cpp src/Core/Game.cpp src/Core/Game.h src/Core/Space.cpp src/Core/Space.h src/Core/Marker.cpp src/Core/Marker.h src/Core/Player.cpp src/Core/Player.h src/GameRenderer/GameRenderer.cpp src/GameRenderer/GameRenderer.h src/Menus/MainMenu.cpp src/Menus/MainMenu.h src/AI/AI.cpp src/AI/AI.h src/Utils/Utils.h src/Utils/Utils.cpp src/Menus/AIMenu.cpp src/Menus/AIMenu.h src/Menus/Menu.cpp src/Menus/Menu.h src/Sound/SoundManager.cpp src/Sound/SoundManager.h src/Menus/SpectatorMenu.cpp src/Menus/SpectatorMenu.h)
add_executable(teeko ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(teeko ${SFML_LIBRARIES})
endif()