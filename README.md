# Match3Algorithm

## Overview

**Match3Algorithm** is a C++ implementation of a Match-3 game logic system that efficiently detects and clears tile matches using graph-based techniques. The project focuses on **tile matching, swapping mechanics, and efficient pattern recognition** using depth-first search (DFS) and adjacency lists.

## Features

- **Graph-Based Board Representation**: Uses an adjacency list instead of a simple 2D grid for more flexibility.
- **Depth-First Search (DFS) for Match Detection**: Efficiently finds and clears matching tiles.
- **Tile Swapping Mechanics**: Allows valid swaps between adjacent tiles.
- **Dynamic Board Updates**: Handles cascading matches and tile refilling.
- **Optimized Performance**: Avoids unnecessary board scans, making it suitable for large-scale Match-3 implementations.

## How It Works

1. **Board Initialization**:
   - The game board is represented as a graph, with each tile as a node and edges connecting adjacent tiles.
   
2. **Tile Swapping**:
   - Players can swap adjacent tiles.
   - The swap is validated to ensure it results in a match.

3. **Match Detection**:
   - DFS is used to search for connected groups of matching tiles.
   - Matching tiles are marked for removal.

4. **Tile Removal & Refill**:
   - Matched tiles are cleared.
   - New tiles drop down to fill empty spaces.
   - The board is checked again for cascading matches.

## Project Structure

```
Match3Algorithm/
│── src/               # Core implementation
│   ├── board.cpp      # Board representation and management
│   ├── tile.cpp       # Tile properties and interactions
│   ├── match.cpp      # Match detection logic (DFS)
│── test/              # Unit tests
│── assets/            # Optional graphical assets (if applicable)
│── README.md          # Project documentation
```

## Installation & Usage

### Prerequisites
- C++11 or later
- CMake (for building)

### Build Instructions

```bash
git clone https://github.com/youssefmyh/Match3Algorithm.git
cd Match3Algorithm
mkdir build && cd build
cmake ..
make
./match3algorithm  # Run the program
```

### Running Tests
```bash
make test
```

## Why This Project?

Match-3 games are a classic genre, and this project provides a **clean, efficient, and scalable** approach to implementing their core mechanics. Whether you're a game developer, a student, or just curious about **graph algorithms in game development**, this project is a great resource.

## Contributing

Contributions are welcome! Feel free to **fork the repo**, open issues, or submit pull requests to enhance the algorithm and add new features.

## License

This project is licensed under the **MIT License**.

## Contact

For questions or suggestions, reach out via [GitHub Issues](https://github.com/youssefmyh/Match3Algorithm/issues).

