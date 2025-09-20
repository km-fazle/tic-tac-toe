---
layout: default
title: Usage Guide
---

# Usage Guide

## Requirements

To compile and run this Tic-Tac-Toe game, you'll need:

- A C++ compiler with C++11 support (like g++, clang++, or MSVC)
- Standard C++ libraries (included with most compilers)
- Basic command-line knowledge

## Compilation

### Using g++ (GNU Compiler)

```bash
g++ -std=c++11 -pthread tic_tac_toe.cpp -o tic_tac_toe
```

### Using clang++ (LLVM Compiler)

```bash
clang++ -std=c++11 -pthread tic_tac_toe.cpp -o tic_tac_toe
```

### Using MSVC (Windows)

```bash
cl /EHsc /std:c++11 tic_tac_toe.cpp
```

## Running the Program

After compilation, you can run the program from the command line:

### On Linux/macOS

```bash
./tic_tac_toe
```

### On Windows

```bash
tic_tac_toe.exe
```

## Expected Output

When you run the program, you'll see:

1. An empty game board is displayed
2. Players X and O take turns making random moves
3. Each move is displayed with an updated board
4. When the game ends, the winner (X or O) or a Cat's Game (draw) is announced

Example output:

```
Starting Tic-Tac-Toe:

   |   |  
---+---+---
   |   |  
---+---+---
   |   |  

 X |   |  
---+---+---
   |   |  
---+---+---
   |   |  

 X |   |  
---+---+---
   | O |  
---+---+---
   |   |  

(further moves...)

 X | O | X
---+---+---
 O | X | O
---+---+---
 X |   | O

Player X has won the game!
```

## Understanding the Game

- The game is fully automated - players make random moves
- No user input is required during gameplay
- The program will terminate automatically when the game ends
- Each player runs in a separate thread, demonstrating concurrent programming techniques

## Modifying the Game

If you want to modify the game or extend its functionality:

1. Open `tic_tac_toe.cpp` in your favorite code editor
2. Make your changes (e.g., adding human player input, improving AI logic)
3. Recompile using the commands above
4. Run the updated executable

## Troubleshooting

Common issues and solutions:

### Compilation Error: "undefined reference to pthread functions"
- Make sure to include the `-pthread` flag when compiling

### Compilation Error: "This file requires compiler and library support for the ISO C++ 2011 standard"
- Use the `-std=c++11` flag (or newer) when compiling

### Unexpected Game Behavior
- Check that your random number generator is properly seeded
- Ensure thread synchronization is working correctly