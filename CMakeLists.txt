# CMakeList.txt: Grand_Palace_Monopoly_memberA 的 CMake 專案，在此包含來源及定義
# 專案專屬邏輯。
#
cmake_minimum_required (VERSION 3.8)
project(Grand_Palace_Monopoly)

# 將來源新增到此專案的可執行檔。
add_executable (Grand_Palace_Monopoly_memberA "Board.cpp" "Board.h" "Player.h" "Player.cpp" "DiceRoller.cpp" "DiceRoller.h" "Tile.h" "Tile.cpp" "main.cpp")

# TODO: 新增測試，並視需要安裝目標。