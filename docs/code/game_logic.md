---
layout: default
title: Game Logic
---

# Game Logic

## Overview

This page explains the core logic of the Tic-Tac-Toe game implementation, including how moves are made, how the game detects wins, and how the threads interact.

## Game Flow

1. The game initializes an empty 3×3 board
2. Two player threads are created (X and O)
3. Players take turns making random moves
4. After each move, the game checks for a win or draw
5. The game ends when a player wins or the board is full (draw)
6. Results are displayed and the program exits

## Thread Synchronization

One of the key features of this implementation is the use of threads and mutexes for player synchronization:

```cpp
void player(Game& g, char mark, int id) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10 * id));
    // ensures threads don't hit the mutex at the same time on startup

    while (true) {
        std::unique_lock<std::mutex> lock(g.m);
        if (g.gameover) {
            break;
        }

        if (g.turn != id) {
            continue;
        }

        // Make move and check for game end conditions
        // ...

        lock.unlock();
    }
}
```

Key synchronization elements:
- Each player thread acquires a lock on the game mutex before checking or modifying the game state
- The `turn` variable controls which player can make a move
- After a player makes a move, they change the `turn` to the other player's ID
- The mutex is unlocked to allow the other player to take their turn

## Move Selection

Moves are selected randomly using C++'s random number generation facilities:

```cpp
int random_selection() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 8);

    int rn = dist(gen);
    return rn;
}
```

The player function uses this to select random empty cells:

```cpp
int selection = random_selection();
while (g.board[selection] != ' ') {
    selection = random_selection();
}
g.board[selection] = mark;
```

## Win Detection

The game checks for wins after each move by examining all possible winning lines:

```cpp
bool check_for_win(const std::array<char, 9>& b, char mark) {
    for (auto line : win_lines) {
        if (b[line[0]] == mark && b[line[1]] == mark && b[line[2]] == mark)
            return true;
    }
    return false;
}
```

The win lines are defined as:
- Rows: [0,1,2], [3,4,5], [6,7,8]
- Columns: [0,3,6], [1,4,7], [2,5,8]
- Diagonals: [0,4,8], [2,4,6]

## Game End Conditions

The game ends when one of these conditions is met:

1. **Win**: A player has three marks in a row (horizontal, vertical, or diagonal)
   ```cpp
   if (check_for_win(g.board, mark)) {
       g.gameover = true;
       g.winner = mark;
       break;
   }
   ```

2. **Draw/Cat's Game**: All 9 cells are filled with no winner
   ```cpp
   else if (g.moves_made == 9) {
       g.gameover = true;
       g.winner = 'C';
       break;
   }
   ```

## Board Representation

The game board is represented as a one-dimensional array of 9 characters:

```cpp
std::array<char, 9> board{};
```

The positions correspond to the following grid:

```
 0 | 1 | 2
---+---+---
 3 | 4 | 5
---+---+---
 6 | 7 | 8
```

Empty cells contain a space character ' ', and player marks are 'X' and 'O'.