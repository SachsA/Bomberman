cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
project(indie_studio)

set(BINARY_NAME bomberman)

set(SRCS_DIR Sources)
set(ERRORS_DIR ${SRCS_DIR}/Errors)

set(CORE_DIR ${SRCS_DIR}/Core)
set(USERDATA_DIR ${CORE_DIR}/UserData)
set(CLOCK_DIR ${CORE_DIR}/Clock)
set(UTILS_DIR ${CORE_DIR}/Utils)

set(BOMBERMAN_DIR ${SRCS_DIR}/BomberMan)

set(CHARACTER_DIR ${BOMBERMAN_DIR}/Character)

set(GAME_DIR ${BOMBERMAN_DIR}/Game)
set(GAMEGFX_DIR ${GAME_DIR}/Gfx)
set(WORLD_DIR ${GAME_DIR}/World)
set(PLAYERS_DIR ${GAME_DIR}/Players)
set(MAP_DIR ${WORLD_DIR}/Map)
set(BLOCKS_DIR ${WORLD_DIR}/Blocks)
set(BOMB_DIR ${WORLD_DIR}/Bomb)
set(BONUS_DIR ${WORLD_DIR}/Bonus)

set(TIMER_DIR ${GAME_DIR}/Timer)
set(MENUS_DIR ${BOMBERMAN_DIR}/Menus)
set(INTRO_GAME_DIR ${MENUS_DIR}/IntroGame)
set(PRINCIPAL_GAME_DIR ${MENUS_DIR}/PrincipalMenuGame)
set(SETTINGS_DIR ${MENUS_DIR}/SettingsMenu)
set(CHOOSE_GAME_DIR ${MENUS_DIR}/ChooseGame)
set(NEW_GAME_DIR ${MENUS_DIR}/NewGame)
set(QUICK_GAME_DIR ${MENUS_DIR}/QuickGame)
set(BOX_DIR ${BLOCKS_DIR}/Box)
set(WALL_DIR ${BLOCKS_DIR}/Wall)
set(BOMBUP_DIR ${BONUS_DIR}/BombUp)
set(POWERUP_DIR ${BONUS_DIR}/PowerUp)
set(SPEEDUP_DIR ${BONUS_DIR}/SpeedUp)
set(AI_DIR ${PLAYERS_DIR}/AI)
set(HUMAN_DIR ${PLAYERS_DIR}/Human)
set(BOMBEXPLOSION_DIR ${BOMB_DIR}/BombExplosion)



set(SRCS
        ${SRCS_DIR}/Main.cpp

        ${CORE_DIR}/Core.cpp
        ${CORE_DIR}/ErrorsCore.cpp
        ${CORE_DIR}/BomberManConfig/BomberManConfig.cpp
        ${CORE_DIR}/BomberManConfig/ErrorsSounds.cpp
        ${CORE_DIR}/BomberManConfig/ErrorsConfig.cpp

        ${CLOCK_DIR}/Clock.cpp

        ${UTILS_DIR}/Utils.cpp

        ${BOMBERMAN_DIR}/BomberMan.cpp
        ${BOMBERMAN_DIR}/ErrorsBomberMan.cpp

        ${MENUS_DIR}/AMenu.cpp

        ${INTRO_GAME_DIR}/IntroGame.cpp
        ${INTRO_GAME_DIR}/ErrorsIntroGame.cpp
        ${INTRO_GAME_DIR}/IntroGameEvent.cpp

        ${PRINCIPAL_GAME_DIR}/PrincipalMenuGame.cpp
        ${PRINCIPAL_GAME_DIR}/ErrorsPrincipalMenuGame.cpp
        ${PRINCIPAL_GAME_DIR}/PrincipalMenuGameEvent.cpp

        ${SETTINGS_DIR}/SettingsMenu.cpp
        ${SETTINGS_DIR}/ErrorsSettingsMenu.cpp
        ${SETTINGS_DIR}/SettingsMenuEvent.cpp

        ${CHOOSE_GAME_DIR}/ChooseGame.cpp
        ${CHOOSE_GAME_DIR}/ErrorsChooseGame.cpp
        ${CHOOSE_GAME_DIR}/ChooseGameEvent.cpp

        ${NEW_GAME_DIR}/NewGame.cpp
        ${NEW_GAME_DIR}/ErrorsNewGame.cpp
        ${NEW_GAME_DIR}/NewGameEvent.cpp

        ${QUICK_GAME_DIR}/QuickGame.cpp
        ${QUICK_GAME_DIR}/ErrorsQuickGame.cpp
        ${QUICK_GAME_DIR}/QuickGameEvent.cpp

        ${ERRORS_DIR}/Errors.cpp

        ${GAMEGFX_DIR}/GameGfx.cpp
        ${GAMEGFX_DIR}/ErrorsGameGfx.cpp
        ${GAMEGFX_DIR}/GameGfxEvent.cpp

        ${BLOCKS_DIR}/ABlock.cpp
        ${BLOCKS_DIR}/ErrorsABlock.cpp

        ${WALL_DIR}/Wall.cpp
        ${WALL_DIR}/ErrorsWall.cpp

        ${BOX_DIR}/Box.cpp
        ${BOX_DIR}/ErrorsBox.cpp

	${TIMER_DIR}/Timer.cpp

        ${BOMB_DIR}/Bomb.cpp
        ${BOMB_DIR}/ErrorsBomb.cpp

	${BOMBEXPLOSION_DIR}/BombExplosion.cpp
	${BOMBEXPLOSION_DIR}/ErrorsBombExplosion.cpp

        ${BONUS_DIR}/ABonus.cpp
        ${BONUS_DIR}/ErrorsABonus.cpp

        ${BOMBUP_DIR}/BombUp.cpp
        ${BOMBUP_DIR}/ErrorsBombUp.cpp

        ${POWERUP_DIR}/PowerUp.cpp
        ${POWERUP_DIR}/ErrorsPowerUp.cpp

        ${SPEEDUP_DIR}/SpeedUp.cpp
        ${SPEEDUP_DIR}/ErrorsSpeedUp.cpp

        ${MAP_DIR}/Map.cpp
        ${MAP_DIR}/ErrorsMap.cpp

        ${PLAYERS_DIR}/APlayer.cpp
        ${PLAYERS_DIR}/ErrorsAPlayer.cpp

        ${AI_DIR}/Ai.cpp
        ${AI_DIR}/ErrorsAi.cpp

        ${HUMAN_DIR}/Human.cpp
        ${HUMAN_DIR}/ErrorsHuman.cpp

        ${WORLD_DIR}/World.cpp
        ${WORLD_DIR}/ErrorsWorld.cpp
        )

include_directories(
        ${SRCS_DIR}

        ${BOMBERMAN_DIR}

        ${CORE_DIR}
        ${CORE_DIR}/BomberManConfig

        ${CONF_DIR}

        ${USERDATA_DIR}

        ${CHARACTER_DIR}

        ${GAME_DIR}

        ${MENUS_DIR}
        ${INTRO_GAME_DIR}
        ${PRINCIPAL_GAME_DIR}
        ${SETTINGS_DIR}
        ${CHOOSE_GAME_DIR}
        ${LOAD_GAME_DIR}
        ${NEW_GAME_DIR}
        ${QUICK_GAME_DIR}

        ${ERRORS_DIR}

        ${GAMEGFX_DIR}

        ${WORLD_DIR}
        ${MAP_DIR}
        ${BLOCKS_DIR}
        ${WALL_DIR}
        ${BOX_DIR}
        ${BOMB_DIR}
	${BOMBEXPLOSION_DIR}
        ${BONUS_DIR}
        ${BOMBUP_DIR}
        ${POWERUP_DIR}
        ${SPEEDUP_DIR}
        ${PLAYERS_DIR}
        ${AI_DIR}
	${TIMER_DIR}
        ${HUMAN_DIR}
)

add_executable(${BINARY_NAME} ${SRCS})

### Linking LIB

if (WIN32)
    set(IRRLICHT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Library/Irrlicht/Windows32)
    set(IRRLICHT_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/Library/Irrlicht/IrrlichtInclude)

    include_directories(${LINK_DIR} ${IRRLICHT_DIR} ${IRRLICHT_INCLUDE})
    link_directories(${LINK_DIR} ${IRRLICHT_DIR})

    find_library(LIB_IRRLICHT Irrlicht HINTS ${IRRLICHT_DIR})

    if (IRRLICHT_INCLUDE)

        target_link_libraries(${BINARY_NAME}
        PUBLIC
        ${LIB_IRRLICHT})
    else ()
        message(WARNING "!!! Irrlicht is missing !!!")
endif()

elseif (UNIX)
    set(CMAKE_CXX_FLAGS "-W -Wextra -Werror")
    set(IRRLICHT_DEPENDENCIES pthread GL X11 Xxf86vm)

	### Installation LINUX

    install(DIRECTORY ${CMAKE_SOURCE_DIR}/Library/Irrlicht/IrrlichtInclude
            DESTINATION /usr/include
            FILE_PERMISSIONS WORLD_READ WORLD_WRITE)

    install(FILES ${CMAKE_SOURCE_DIR}/Library/Irrlicht/Linux/libIrrlicht.a
            DESTINATION /usr/lib)

    install(FILES ${CMAKE_SOURCE_DIR}/Library/SFMLAudio/Linux/libsfml-audio.so
            DESTINATION /usr/lib)

    install(DIRECTORY ${CMAKE_SOURCE_DIR}/AssetsIndie
            DESTINATION /usr/bin
            FILE_PERMISSIONS WORLD_READ WORLD_WRITE)

    install(DIRECTORY ${CMAKE_SOURCE_DIR}/AssetsIndie
            DESTINATION /usr/local/bin
            FILE_PERMISSIONS WORLD_READ WORLD_WRITE)

    install(DIRECTORY ${CMAKE_SOURCE_DIR}/ConfigIndie
            DESTINATION /usr/bin
            FILE_PERMISSIONS WORLD_READ WORLD_WRITE)

    install(DIRECTORY ${CMAKE_SOURCE_DIR}/ConfigIndie
            DESTINATION /usr/local/bin
            FILE_PERMISSIONS WORLD_READ WORLD_WRITE)

    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${BINARY_NAME}
            DESTINATION /usr/bin/
            PERMISSIONS WORLD_EXECUTE)

    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${BINARY_NAME}
            DESTINATION /usr/local/bin/
            PERMISSIONS WORLD_EXECUTE)
    find_path(IRRLICHT_INCLUDE_DIRECTORY
            NAMES irrlicht.h
            PATHS /usr/include
            ${CMAKE_CURRENT_SOURCE_DIR}/Library/Irrlicht/IrrlichtInclude)
    find_path(SFML_INCLUDE_DIRECTORY
            NAMES Audio.hpp
            PATHS /usr/include
            ${CMAKE_CURRENT_SOURCE_DIR}/Library/SFMLAudio/SFMLInclude/SFML)
    find_library(IRRLICHT_LIBRARY
            NAMES libIrrlicht.a
            PATHS /usr/lib/
            ${CMAKE_CURRENT_SOURCE_DIR}/Library/Irrlicht/Linux)
    find_library(SFMLAUDIO_LIBRARY
            NAMES libsfml-audio.so
            PATHS /usr/lib/
            ${CMAKE_CURRENT_SOURCE_DIR}/Library/SFMLAudio/Linux)

    include_directories(${IRRLICHT_INCLUDE_DIRECTORY})
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Library/SFMLAudio/SFMLInclude)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Library/SFMLAudio/SFMLInclude/Audio)
    include_directories(${SFML_INCLUDE_DIRECTORY})

    if (IRRLICHT_LIBRARY AND SFMLAUDIO_LIBRARY AND SFML_INCLUDE_DIRECTORY AND IRRLICHT_INCLUDE_DIRECTORY)
        target_link_libraries(${BINARY_NAME}
                PUBLIC
                ${IRRLICHT_DEPENDENCIES}
                ${IRRLICHT_LIBRARY}
                ${SFMLAUDIO_LIBRARY}
                )
    else ()
        message(WARNING "*** Irrlicht/Irrlicht Includes or SFML/SFML Includes not found, build failed! ***")
    endif ()

endif ()
