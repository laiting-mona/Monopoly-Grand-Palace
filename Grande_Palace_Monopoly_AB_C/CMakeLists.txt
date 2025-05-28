cmake_minimum_required(VERSION 3.10)
project(GrandePalaceMonopoly)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Game)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Cards)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Tiles)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/MiniGames)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Commands)

# Source and header files
set(SOURCES
    Main.cpp

    Game/Game.cpp
    Game/Game.hpp
    Game/Board.cpp
    Game/Board.hpp
    Game/Player.cpp
    Game/Player.hpp
    Game/GameConfig.cpp
    Game/GameConfig.hpp
    Game/CardStore.cpp
    Game/CardStore.hpp
    Game/Bank.cpp
    Game/Bank.hpp
    Game/SingletonManager.cpp
    Game/SingletonManager.hpp
    Game/Utils.cpp
    Game/Utils.hpp
    Game/GameRecorder.cpp
    Game/GameRecorder.hpp
    Game/MiniGameManager.cpp
    Game/MiniGameManager.hpp
    Game/InputManager.hpp
    Game/BotPlayer.cpp
    Game/BotPlayer.hpp
    Game/Error.hpp

    Cards/Card.cpp
    Cards/Card.hpp
    Cards/FateCard.cpp
    Cards/FateCard.hpp
    Cards/RocketCard.cpp
    Cards/RocketCard.hpp
    Cards/DiceControlCard.cpp
    Cards/DiceControlCard.hpp
    Cards/BarrierCard.cpp
    Cards/BarrierCard.hpp
    Cards/DemolitionCard.cpp
    Cards/DemolitionCard.hpp
    Cards/TollCard.cpp
    Cards/TollCard.hpp

    Tiles/Tile.hpp
    Tiles/MiniGameTile.cpp
    Tiles/MiniGameTile.hpp
    Tiles/StartTile.cpp
    Tiles/StartTile.hpp
    Tiles/StoreTile.cpp
    Tiles/StoreTile.hpp
    Tiles/EventTile.cpp
    Tiles/EventTile.hpp
    Tiles/HospitalTile.cpp
    Tiles/HospitalTile.hpp
    Tiles/PropertyTile.cpp
    Tiles/PropertyTile.hpp

    MiniGames/MiniGame.hpp
    MiniGames/DragonGateGame.cpp
    MiniGames/DragonGateGame.hpp
    MiniGames/HorseRaceGame.cpp
    MiniGames/HorseRaceGame.hpp

    Commands/Command.hpp
    Commands/CommandManager.hpp
    Commands/ChangePhaseCommand.hpp
    Commands/GainCardCommand.hpp
    Commands/GainMoneyCommand.hpp
    Commands/ListCommandsCommand.hpp
    Commands/MoveToCommand.hpp
    Commands/ShowAllPlayersCommand.hpp
    Commands/TransferMoneyCommand.hpp
    Commands/TriggerMiniGameCommand.hpp
    Commands/CommandManager.cpp
    Commands/ChangePhaseCommand.cpp
    Commands/GainCardCommand.cpp
    Commands/GainMoneyCommand.cpp
    Commands/ListCommandsCommand.cpp
    Commands/MoveToCommand.cpp
    Commands/ShowAllPlayersCommand.cpp
    Commands/TransferMoneyCommand.cpp
    Commands/TriggerMiniGameCommand.cpp


)

add_executable(${PROJECT_NAME} ${SOURCES})
configure_file(${CMAKE_SOURCE_DIR}/config.json ${CMAKE_BINARY_DIR}/config.json COPYONLY)

