# C++ Ping Pong using Raylib

A fast-paced, cross-platform Pong clone built with **C++** and **Raylib**. Featuring increasing ball velocity and smooth paddle physics.

## How to Play

The game is a classic 2-player local match. First one to miss the ball gives a point to the opponent!

| Action | Player 1 (Left) | Player 2 (Right) |
| :--- | :--- | :--- |
| **Move Up** | `W` | `Up Arrow` |
| **Move Down** | `S` | `Down Arrow` |
| **Launch Ball** | `Space` | `Space` |

## Downloads

You can find pre-compiled executables for **Windows** and **Linux** in the [Releases](https://github.com/RamOfFate/cpp-ping-pong/releases) section.

* **Windows**: Download `Pong-Win.exe` and run. No installation required!
* **Linux**: Download `Pong-Linux`, give it execute permissions (`chmod +x Pong-Linux`), and run.

## Tech Stack
* **Language:** C++17
* **Library:** [Raylib](https://www.raylib.com/)
* **Build System:** GitHub Actions (Automated Cross-Platform Builds)
* **OS:** Developed on EndeavourOS (Arch Linux)

## Building from Source

If you want to compile it yourself:

### Linux (Arch/EndeavourOS)
1. Install dependencies: `sudo pacman -S raylib mesa-utils`
2. Compile: `g++ src/main.cpp -o Pong -lraylib -lGL -lm -lpthread -ldl -lrt -lX11`
3. Run: `./Pong`

### Windows
The easiest way is to use the provided GitHub Actions workflow or a C++ compiler with Raylib installed via `vcpkg`.
