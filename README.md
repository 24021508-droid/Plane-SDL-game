# ✈️ Plane Battle — A 2D Top-Down Shooter

A 2D top-down airplane shooting game built with **C++** and **SDL2**. Battle through waves of enemies, survive boss fights, and master special bullet mechanics to win!

---

## 📋 Table of Contents

- [About the Game](#-about-the-game)
- [Features](#-features)
- [Gameplay](#-gameplay)
- [Controls](#-controls)
- [Game Mechanics](#-game-mechanics)
- [Wave System](#-wave-system)
- [Project Structure](#-project-structure)
- [Architecture Overview](#-architecture-overview)
- [Dependencies](#-dependencies)
- [Building the Project](#-building-the-project)
- [Known Issues](#-known-issues)

---

## 🎮 About the Game

**Plane Battle** is a classic arcade-style top-down shooter where you pilot a fighter plane against waves of increasingly difficult enemies and boss characters. The game was built using C++ with the SDL2 library for rendering, audio, and input handling.

- **Window size:** 1280 × 720 (16:9)
- **IDE / Build System:** Code::Blocks with GCC (MinGW)
- **Language:** C++
- **Libraries:** SDL2, SDL2_image, SDL2_ttf, SDL2_mixer

---

## ✨ Features

- Smooth player movement with arrow keys
- Normal and special (triple) bullet modes
- Energy bar system — charge by defeating enemies, then activate special bullets
- HP bar displayed on screen in real time
- Enemy waves that grow in size and speed over time
- Smart enemies that track the player when close (within 300 px)
- 3 unique Boss characters (waves 3, 6, and 8)
- Win screen after surviving 8 waves
- Game Over screen with Replay / Quit options
- Main menu with Start and Quit buttons
- Wave counter displayed on screen

---

## 🕹️ Gameplay

The game is divided into **8 waves**. In each wave, you must eliminate all enemies before the next wave spawns:

| Wave | Content |
|------|---------|
| 1    | 2 standard enemies |
| 2    | auto-generated enemies via spawnWave() |
| 3    | **Boss 1** (boss_1.png) |
| 4    | auto-generated enemies |
| 5    | auto-generated enemies |
| 6    | **Boss 2** (boss_2.png) |
| 7    | auto-generated enemies |
| 8    | **Boss 3** (boss_3.png) |

After wave 8, a **You Win!** screen is displayed.

---

## 🎮 Controls

| Key | Action |
|-----|--------|
| Arrow Keys (←→↑↓) | Move the player |
| SPACE | Shoot a bullet |
| 1 | Activate special (triple) bullet — requires full energy bar |
| P | Pause / return to main menu |

---

## ⚙️ Game Mechanics

### Player
- **HP:** 60 (displayed as a red health bar)
- **Speed:** 10 px per frame
- **Damage taken per hit:** 2 HP
- Uses a **cross-shaped hitbox** (vertical strip + horizontal strip) for more precise collision detection

### Energy / Special Bullet System
- Killing a regular enemy grants **+5 energy**; hitting a boss grants **+10 energy**
- Max energy: **60**
- Press `1` when energy is full to activate **triple-shot mode** for 10 seconds
- Energy drains gradually during special mode; the energy bar turns **orange** while active (green when normal)

### Enemy Behavior
- **Standard enemies** (speed 1): Zigzag across the screen
- **Fast enemies** (speed 2, 20% spawn chance): Same zigzag pattern but faster
- When an enemy comes within **300 px** of the player it switches to **homing mode** — it chases the player directly
- Enemies randomly fire bullets downward (1% chance per frame)
- Enemy HP: **2**

### Boss Behavior
- Moves horizontally back and forth across the screen at speed 2
- Has **30 HP**
- Fires a **3-bullet spread** (cone pattern) with a 2% chance per frame:
  - 1 center bullet (damage 10)
  - 2 side bullets at ±50px offset (damage 5 each)

---

## 🌊 Wave System

- A new wave is triggered when **all enemies and bosses are cleared**
- The `spawnWave()` static method calculates how many enemies to spawn:
  - Base: 2 enemies + bonus based on elapsed time
  - Enemies spawn from the left edge, right edge, or center top
- Minimum interval between waves: **6000 ms** (6 seconds)

---

## 📁 Project Structure

```
GAME-main/
├── Game_2.exe              # Prebuilt Windows executable
├── README.md               # This file
├── images/                 # All game image assets
│   ├── background.png
│   ├── menu.png
│   ├── khongphut.PNG       # Player sprite
│   ├── enemy.PNG
│   ├── special_enemy.png
│   ├── boss_1.png
│   ├── boss_2.png
│   ├── boss_3.png
│   ├── bullet.png / onebullet.PNG
│   ├── triple_bullet.png
│   ├── bullet2.png / bullet3.png
│   ├── enemybullet.PNG
│   ├── StartButton.png / QuitButton.png
│   ├── yes.png / no.png
│   ├── Game_over.png
│   └── you_win.png
└── bin/                    # Source code
    ├── main.cpp            # Entry point, game loop, wave management
    ├── CommonFunc.h        # SDL globals & function declarations
    ├── CommnonFunc.cpp     # SDL initialization/shutdown implementation
    ├── player.h/.cpp       # Player class
    ├── enemy.h/.cpp        # Enemy class + wave spawning
    ├── boss.h/.cpp         # Boss class
    ├── Bullet.h/.cpp       # Bullet class (shared by player, enemy, boss)
    ├── button.h            # Button & Menu class declarations
    ├── menu.cpp            # Button & Menu class implementation
    └── Game_2.cbp          # Code::Blocks project file
```

---

## 🏗️ Architecture Overview

```
main.cpp
 ├── CommonFunc        — SDL2 init/quit, global window/renderer/font
 ├── Menu              — Main menu (background + Start/Quit buttons)
 ├── Button            — Reusable clickable UI button
 ├── Player            — Movement, shooting, health, energy, hitboxes
 ├── Enemy             — AI movement, homing, shooting, wave spawning
 ├── Boss              — Horizontal movement, spread shot, health
 └── Bullet            — Shared projectile class (player + enemy + boss)
```

### Class Responsibilities

| Class | File | Responsibility |
|-------|------|----------------|
| `Player` | player.h / player.cpp | Movement, rendering, hitbox, HP, energy, special bullet state |
| `Enemy` | enemy.h / enemy.cpp | AI (zigzag + homing), shooting, static wave spawning |
| `Boss` | boss.h / boss.cpp | Horizontal bounce movement, spread shooting, health tracking |
| `Bullet` | Bullet.h / Bullet.cpp | Generic projectile: move, render, rect, damage, out-of-screen check |
| `Button` | button.h / menu.cpp | Clickable SDL2 texture button with rectangular hit-test |
| `Menu` | button.h / menu.cpp | Main menu screen with background image and two buttons |
| `CommonFunc` | CommonFunc.h / CommnonFunc.cpp | SDL2 + TTF init/shutdown, global `g_window`, `g_screen`, `g_event`, `g_font` |

---

## 📦 Dependencies

| Library | Version (used during dev) | Purpose |
|---------|--------------------------|---------|
| SDL2 | 2.x | Window, renderer, event loop, input |
| SDL2_image | 2.6.3 | PNG/image loading via `IMG_LoadTexture` |
| SDL2_ttf | 2.20.2 | TrueType font rendering (wave counter HUD) |
| SDL2_mixer | 2.x | Audio (header included, not fully implemented) |

---

## 🔨 Building the Project

### Prerequisites
- [Code::Blocks](https://www.codeblocks.org/) with MinGW GCC
- SDL2 development libraries installed (default path: `C:/SDL2/`)
- SDL2_image development libraries
- SDL2_ttf development libraries

### Build Steps

1. Open `bin/Game_2.cbp` in **Code::Blocks**
2. Adjust the compiler include directories and linker library directories in **Project → Build Options** to match your local SDL2 installation paths
3. Update all **hardcoded asset paths** in the source files (see note below)
4. Press **Build & Run** (F9)

> **Important:** All image and font paths are currently hardcoded to:
> ```
> D:\gamestart_1\game start 1\Game_2\picture\...
> ```
> You must update every occurrence of these paths to match your local directory, or place assets at that exact location.

### Linked Libraries (from project file)

```
-lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lstdc++ -lSDL2_image -lsetupapi
```

---

## ⚠️ Known Issues

| Issue | Description |
|-------|-------------|
| **Hardcoded asset paths** | All image/font paths are absolute (`D:\gamestart_1\...`). Must be updated per machine. |
| **Double boss render** | `boss.move()` and `boss.render()` are called twice per frame loop in some branches of `main.cpp`, causing minor redundant draw calls. |
| **Filename typo** | The implementation file is named `CommnonFunc.cpp` (double `n`) instead of `CommonFunc.cpp`. |
| **No audio** | SDL2_mixer is linked but no sound effects or music are implemented. |
| **Bullet texture leak** | SDL textures loaded per `Bullet` instance are not explicitly freed when bullets are erased from vectors. |

---

## 👨‍💻 Development Notes

- The game loop runs at approximately **60 FPS** (`SDL_Delay(16)` per frame)
- Collision detection uses `SDL_HasIntersection()` with cross-shaped hitboxes
- The wave counter starts at 0; victory triggers when `waveCount > 8` with no bosses remaining
- Game state is managed with a simple `GameState` enum: `STATE_MENU`, `STATE_PLAYING`, `STATE_EXIT`

---

*Built with C++ and SDL2*
