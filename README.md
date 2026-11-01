# Overview

A maze generation program written in C using Raylib that visualizes Randomized Prim's Algorithm in real time. The program begins with a randomly selected cell and progressively constructs a maze by expanding into neighboring cells.

## Installation

This project provides both a pre-compiled Windows executable for quick testing and the source files for manual compilation.

### Option 1: Run the Pre-compiled Executable (Windows Quick Start)
1. Download the pre-packaged application here: **[Download mazeGen.zip](https://github.com/Bossbongo/Maze-generator/releases/tag/V1.0.0)**
2. Extract the ZIP archive to your preferred folder.
3. Double-click `mazeGen.exe` to launch the visualizer.

### Option 2: Manual Build from Source
Ensure you have GCC and [Raylib](https://raylib.com) configured in your compiler paths.

```bash
# Clone the repository
git clone https://github.com
cd maze-generator

# Compile the source code
gcc mazeGen.c -lraylib -lopengl32 -lgdi32 -lwinmm -o bin/mazeGen.exe
```

## Features
- Generates mazes using Randomized Prim's Algorithm
- Real-time visualization of maze construction.
- Random starting position
- Grid-based maze reputation
- Built using the Raylib graphics library
## Technologies Used

Language: C

Graphics: Raylib

## Technical Architecture
- 1D Array grid mapping: Represented the 2D maze as a 1D array
- Custom Coordinate Structure: Keeping track of Cell states (visited and unvisited)
