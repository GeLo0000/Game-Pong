# Pong Game

Implementation of the classic Pong game built with C++ and SFML 3.0.2.

## Technologies

- **Language:** C++ (C++17)
- **Graphics:** SFML 3.0.2
- **Build System:** CMake 3.28+
- **Platform:** Windows, Linux
- **Compiler:** GCC (g++)

## Features

- **Two Game Modes:**
  - Player vs Player
  - Player vs Bot

- **Game Mechanics:**
  - Dynamic ball acceleration on each paddle hit
  - Collision detection with paddles, walls, and boundaries
  - Score tracking and display
  - Pause/Resume functionality

- **User Interface:**
  - Main menu for mode selection with mouse and keyboard support
  - In-game UI showing score and ball velocity
  - Pause menu

- **Audio System:**
  - Background music during gameplay
  - Sound effects for paddle hits, wall bounces, and goals

## Architecture

### Object-Oriented Principles

- **Encapsulation:** Each component manages its own state
- **Inheritance:** IGameObject base class for game entities (Paddle, Ball)
- **Polymorphism:** Virtual methods for draw(), update(), getBounds()
- **Abstraction:** Clear interfaces for UI element (IUIElement)

### Design Patterns

- **Singleton Pattern:** EventManager, ResourceManager
- **Observer Pattern:** Event-driven architecture via EventManager
- **Factory Pattern:** GameObjectFactory for object creation

## Installation & Setup

The project uses CMake with automatic SFML 3.0.2 download via FetchContent. No manual SFML installation required.

### Windows

**Prerequisites:**
- [Git](https://git-scm.com/download/win)
- [CMake](https://cmake.org/download/) (3.28 or later)
- [MinGW-w64](https://www.mingw-w64.org/) or [MSYS2](https://www.msys2.org/) with g++

**Build Steps:**

1. Clone the repository:
   ```powershell
   git clone https://github.com/GeLo0000/Game-Pong.git
   cd Game-Pong
   ```

2. Create build directory:
   ```powershell
   mkdir build
   cd build
   ```

3. Generate build files and compile:
   ```powershell
   cmake .. -G "MinGW Makefiles"
   cmake --build .
   ```

4. Run the game:
   ```powershell
   .\bin\Game-Pong.exe
   ```

### Linux


**Ubuntu/Debian:**
```bash
# Install dependencies
sudo apt update
sudo apt install build-essential git cmake libxrandr-dev libxcursor-dev libxi-dev libudev-dev libfreetype-dev libflac-dev libvorbis-dev libgl1-mesa-dev libegl1-mesa-dev libfreetype-dev

# Clone and build
git clone https://github.com/GeLo0000/Game-Pong.git
cd Game-Pong
mkdir build && cd build
cmake ..
cmake --build .

# Run
./bin/Game-Pong
```
## How to Play

### Controls

**Main Menu:**
- Press `1` or **Click** "Player vs Player" button to select PvP mode
- Press `2` or **Click** "Player vs Bot" button to select PvB mode
- Press `ESC` to exit

**During Gameplay:**
- **Left Paddle:** `W` (Up) / `S` (Down)
- **Right Paddle:** `↑` (Up) / `↓` (Down) in PvP mode, or Bot moves automatically in PvB mode
- **`Space`:** Pause/Resume game
- **`R`:** Restart round
- **`M`:** Return to main menu
- **`ESC`:** Exit game

## Download
- Download: [Game-Pong for Windows](https://github.com/GeLo0000/Game-Pong/releases/download/v1.1/Game-Pong_v1.1_Windows_x64.zip)
