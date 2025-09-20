---
layout: default
title: Code Structure
---

# CSCI-310 - Group 1: Code Structure

## Overview

The Tic-Tac-Toe game is implemented in C++ using multiple components that work together to create a functional game. This document explains the key components and their roles.

## Source Files

- `tic_tac_toe.cpp`: The main source file containing all game logic

## Key Components

### Game Structure

The game state is managed through the `Game` structure:

```cpp
struct Game {
    std::array<char, 9> board{};
    std::mutex m;
    int turn = 0;               // This can either be 0 or 1 to indicate which player gets to play
    bool gameover = false;      // boolean to set game end state
    char winner = ' ';          // This will be X, O, or C (Cat's Game) if gameover True and ' ' if gameover false
    int moves_made = 0;         // let the game count # of moves made

    Game() {                    // this is a constructor which will initialize our gameboard and fill it with empty spaces
        board.fill(' ');
    }
};
```

This structure stores:
- The game board as a 1D array of 9 characters
- A mutex for thread synchronization
- Turn tracking (0 for player X, 1 for player O)
- Game state (whether the game is over)
- Winner tracking (X, O, or C for Cat's Game/Draw)
- Move counter

### Win Condition Checking

Win conditions are stored in a 2D array representing all possible winning lines:

```cpp
static const int win_lines[8][3] = {    // creates a 2D array for referencing the winning lines
    {0,1,2},{3,4,5},{6,7,8},   // rows
    {0,3,6},{1,4,7},{2,5,8},   // cols
    {0,4,8},{2,4,6}            // diagonals
};
```

### Key Functions

#### Board Display

The `print_board()` function visualizes the current game state in the console:

```cpp
void print_board(const Game& g) {
    std::cout << '\n';
    std::cout << " " << g.board[0] << " | " << g.board[1] << " | " << g.board[2] << "\n";
    std::cout << "---+---+---\n";
    std::cout << " " << g.board[3] << " | " << g.board[4] << " | " << g.board[5] << "\n";
    std::cout << "---+---+---\n";
    std::cout << " " << g.board[6] << " | " << g.board[7] << " | " << g.board[8] << "\n";
    std::cout.flush();   // clears cout buffer to make sure that threads don't overlap their prints
}
```

#### Win Checking

The `check_for_win()` function determines if a player has won:

```cpp
bool check_for_win(const std::array<char, 9>& b, char mark) {
    for (auto line : win_lines) {
        if (b[line[0]] == mark && b[line[1]] == mark && b[line[2]] == mark)
            return true;
    }
    return false;
}
```

#### Random Move Selection

The `random_selection()` function generates random moves for the AI players:

```cpp
int random_selection() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 8);

    int rn = dist(gen);
    return rn;
}
```

#### Player Logic

The `player()` function contains the logic for each player's turn:

```cpp
void player(Game& g, char mark, int id) {
    // Function implementation handles:
    // - Thread synchronization
    // - Turn taking
    // - Move selection
    // - Win/draw detection
}
```

#### Main Function

The `main()` function initializes the game and creates threads for the players:

```cpp
int main() {
    Game g;
    // Initialize game, create player threads, 
    // join threads, and display results
}
```

## Threading Model

The game uses C++ threads to run the two players concurrently:

1. Each player (X and O) runs in its own thread
2. A mutex (`g.m`) ensures that only one player can access the game state at a time
3. Players take turns by checking the `turn` variable
4. Thread synchronization is handled with `std::unique_lock<std::mutex>`
5. The mutex-protected design prevents race conditions and ensures game state integrity

## Memory Management

The game uses standard C++ containers and automatic memory management:
- `std::array<char, 9>` for the game board
- No dynamic memory allocation
- Stack-based objects