---
title: Grande Palace Monopoly

---

# Grande Palace Monopoly

## 一、專案簡介

Grande Palace Monopoly 是一款以經典壟斷遊戲為基礎的策略桌遊電腦版，使用 ASCII 輸出於 Windows 10 終端機環境中執行。
遊戲支援多人本機同樂，並結合多種策略卡片與小遊戲，包含射龍門和賭馬等玩法，增添遊戲趣味與多樣性。

本專案使用 C++17 語言開發，並以 CMake 作為建置系統，方便跨平台編譯與維護。

## 二、主要特色

* **多種地圖布局**：經典周邊環狀、多層立體及隨機拼板三種地圖。
* **豐富勝利條件**：包括資產累積達標、區域控制與積分制。
* **多樣卡片系統**：RocketCard、DiceControlCard、BarrierCard、FateCard 等具體卡片效果。
* **AI玩家支援**：玩家可選擇與人機一同遊玩，AI行為由 BotPlayer 實作。
* **小遊戲機制**：射龍門與賭馬小遊戲作為遊戲過程的一部分。
* **存檔與重播**：支援自動與手動存檔，並可觀看遊戲回放。

## 三、專案結構

```
/                      # 專案根目錄
├── Main.cpp           # 遊戲主程式入口
├── CMakeLists.txt     # CMake 建置設定檔
├── command.json       # 遊戲指令設定檔（JSON格式）
├── config.json        # 遊戲設定檔（JSON格式）
├── dialogue.json      # 遊戲對話文本（JSON格式）
├── save/              # 遊戲存檔與日誌資料夾（包含 json 檔）
│   ├── save.json      # 自動及手動存檔資料
│   └── log.json       # 遊戲行動紀錄
│
├── Game/              # 核心遊戲邏輯模組
│   ├── Game.cpp
│   ├── Game.hpp
│   ├── GameConfig.cpp
│   ├── GameConfig.hpp
│   ├── CardStore.cpp
│   ├── CardStore.hpp
│   ├── Bank.cpp
│   ├── Bank.hpp
│   ├── InputManager.hpp
│   ├── Error.hpp
│   ├── SingletonManager.cpp
│   ├── SingletonManager.hpp
│   ├── Utils.cpp
│   ├── Utils.hpp
│   ├── GameRecorder.cpp
│   ├── GameRecorder.hpp
│   ├── MiniGame.hpp
│   ├── MiniGameManager.cpp
│   ├── MiniGameManager.hpp
│   ├── BotPlayer.cpp
│   └── BotPlayer.hpp
│
├── Cards/             # 卡片功能模組
│   ├── Card.cpp
│   ├── Card.hpp
│   ├── FateCard.cpp
│   ├── FateCard.hpp
│   ├── RocketCard.cpp
│   ├── RocketCard.hpp
│   ├── DiceControlCard.cpp
│   ├── DiceControlCard.hpp
│   ├── BarrierCard.cpp
│   ├── BarrierCard.hpp
│   ├── DemolitionCard.cpp
│   └── DemolitionCard.hpp
│
├── Tiles/             # 地圖格子模組
│   ├── Tile.hpp
│   ├── StartTile.cpp
│   ├── StartTile.hpp
│   ├── StoreTile.cpp
│   ├── StoreTile.hpp
│   ├── EventTile.cpp
│   ├── EventTile.hpp
│   ├── HospitalTile.cpp
│   ├── HospitalTile.hpp
│   ├── PropertyTile.cpp
│   └── PropertyTile.hpp
│
└── MiniGames/         # 小遊戲實作模組
    ├── DragonGateGame.cpp   # 射龍門
    ├── DragonGateGame.hpp
    ├── HorseRaceGame.cpp    # 賭馬
    └── HorseRaceGame.hpp
```

## 四、現有的遊戲功能

### 4.1 遊戲核心與流程

* **多種地圖支持**

  * 經典周邊環狀地圖
  * 多層立體地圖
  * 隨機拼板地圖
* **玩家選擇與人數設定**

  * 玩家可選擇2至4人遊戲人數
  * 可選擇是否包含人機玩家，AI自動生成名稱且避免重複
* **玩家行動流程**

  * 擲骰移動
  * 地圖格子互動（購買地皮、支付過路費、觸發事件）
  * 使用卡片
* **回合管理與跳過回合機制**

  * 自動切換玩家順序
  * 玩家無法行動時自動跳過
* **勝利條件支持**

  * 資產達標（財富目標）
  * 控制關鍵地塊/區域（連續持有一定回合數）
  * 積分制（可依照遊戲中規則獲取分數）
* **AI玩家 (BotPlayer)**

  * 基礎策略自動行動（購買地皮、卡片使用等）
  * 隨機姓名生成，與真人不重複
* **存檔與重播系統（GameRecorder）**

  * 支援遊戲狀態存取（自動備份與手動存檔）
  * 遊戲行動日誌紀錄（擲骰、購買、卡片使用等關鍵行動）
  * 遊戲回放功能，可觀看完整回合流程

### 4.2 卡片系統

* 已實作的卡片：

  * RocketCard
  * DiceControlCard
  * BarrierCard
  * FateCard（命運卡）
  * DemolitionCard
* 卡片功能：

  * 觸發特定遊戲事件（移動、獲利或損失、阻擋等）
  * 玩家可在回合中使用卡片，影響遊戲局勢

### 4.3 小遊戲系統

* 射龍門（DragonGateGame）

  * 小遊戲界面與規則完整
  * 作為玩家停留特定地塊時強制觸發的遊戲
  
* 賭馬（HorseRaceGame）

  * 小遊戲界面與規則完整
  * 玩家參與賭注與競賽，影響遊戲資產與積分
  
* 小遊戲管理器（MiniGameManager）

  * 管理多款小遊戲的啟動與結束
  * 與主遊戲流程無縫結合

### 4.4 UI與輸入系統

* ASCII 文字終端界面
* 人機交互指令解析（command.json）
* 對話文本管理（dialogue.json）
* 設定檔讀取與遊戲配置（config.json）

### 4.5 未來功能規劃（待補充）

* 完善 AI 策略與行為
* 強化存檔回放的斷點載入功能
* 小遊戲新增更多種類與深度(待整合聖傑程式碼)
* 改良終端介面呈現與互動
* 優化遊戲平衡與玩家體驗

## 五、建置與執行

1. 確認系統已安裝 CMake（版本 3.10 以上）與 C++17 編譯器（例如 g++ 7+ 或 MSVC 2017+）。

2. 開啟終端機，切換至專案根目錄。

3. 執行以下指令建置：

   ```
   mkdir -p build
   cd build
   cmake ..
   make
   ```

4. 建置完成後，執行產生的可執行檔（Windows 上可能為 `.exe`），即可進入 ASCII 介面遊戲。

## 六、作者

* 賴亭穎 (Tingying Lai)
* 曾秀寧 (Hsuning Zeng)
* 林聖傑 (Shengjie Lin)
* 倪瑞恩 (Ruien Ni)

## 七、授權條款

本專案採用 [MIT License](https://opensource.org/licenses/MIT)，歡迎自由使用、修改與散佈。

## 八、聯絡資訊

如有任何問題或建議，歡迎透過專案 Issue 或 Email 聯繫。

---

**謝謝您的遊玩，祝遊戲愉快！**