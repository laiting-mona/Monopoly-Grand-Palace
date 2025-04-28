# Monopoly Grand Palace

A C++14 project simulating a classic Monopoly board game with modular design, command-based UI, and object-oriented programming principles.

> Developed by three Computer Science freshmen within 4 weeks.  
> Built with C++14 and CMake.

---

## Project Structure

- **Engine**: Core game logic (player movement, property management, turn alternation)
- **Data & Cards**: JSON config loading, card effect system, event triggering
- **UI & Commands**: Terminal text-based UI using ANSI codes, user command parsing

---

## Main Features

- 8x8 board map with special event tiles and mini-games
- Fair dice rolls and player-controlled movement
- Property purchase, upgrade, and selling
- Card system: dice control, property destruction, player hospitalization
- Cheat commands for developer testing
- Modular C++ source code (separated by Engine, Data, UI)
- CMake based build system
- No GUI frameworks (Qt) used, pure terminal interface
- No network connection features implemented

---

## How to Build

```bash
mkdir build
cd build
cmake ..
make
./monopoly
```

> Requirement: CMake 3.28+, C++14 supported compiler

---

## Current Progress

- [x] Base board setup
- [x] Player movement and turn control
- [x] Property buying, upgrading, and rent collection
- [x] Cheat command system
- [x] JSON loading for settings and cards
- [ ] Bot player (optional)
- [ ] Save/load game progress (optional)

---

## Team Members

| Name | Responsibility |
|:-----|:----------------|
| **A** | Core Engine Development |
| **B** | Data Management & Card System |
| **C** | Command Parsing & User Interface |

---

## License

This project is intended for academic and educational purposes only.

---

## 中文簡短描述

大富翁遊戲（C++課程專案），支援文字介面操作、卡片系統與地圖管理，適合OOP設計與模組化實作，使用CMake建置。
