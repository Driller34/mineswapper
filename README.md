# MineSwapper

MineSwapper is a modern C++ implementation of the classic Minesweeper game, featuring a user-friendly graphical interface and extensible architecture.

## Features

- Classic Minesweeper gameplay: Uncover all non-mine cells to win!
- Customizable board size and mine count through flexible game settings
- Smooth and interactive GUI built with SFML
- First-move safety: ensures your first dig is never a mine
- Efficient game logic and dynamic board management
- Flagging system for marking suspected mines
- Easily extensible codebase for new features or modes

## Technologies Used

- C++20
- [SFML 3.0](https://www.sfml-dev.org/) for graphics and window management
- CMake for cross-platform building

## Getting Started

1. **Clone the repository:**
   ```bash
   git clone https://github.com/Driller34/mineswapper.git
   cd mineswapper
   ```

2. **Build the project:**
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ./mineswapper
   ```

3. **Play!**  
   - Left-click to uncover a cell
   - Right-click to place or remove a flag

## Contributing

Contributions, bug reports, and suggestions are welcome! Please open an issue or submit a pull request.

## License

This project is open source. Please add a license file of your choice (e.g., MIT, GPL).

---

Enjoy playing and hacking on MineSwapper!
