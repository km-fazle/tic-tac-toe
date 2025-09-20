---
layout: default
title: Tic-Tac-Toe Documentation
---

# CSCI-310 - Group 1: Tic-Tac-Toe Game

## Overview

This is a simple implementation of the classic Tic-Tac-Toe game in C++. The game features two AI players that make random moves on a 3×3 grid. The program demonstrates concurrent programming using threads in C++, with each player running in its own thread.

## Authors

This project was developed by Group 1:
- Caleb Fitzsimonds
- Sundus Mahamud
- K.M Fazle Rabbi
- Sundus Mahamud
- K.M Fazle Rabbi

## Features

- Two AI players (X and O) playing against each other
- Concurrent execution using C++ threads
- Random move selection
- Automatic win detection
- Clean console display of the game board

## Game Rules

1. The game is played on a 3×3 grid
2. Player X goes first, followed by Player O
3. Players alternate placing their mark (X or O) in an empty cell
4. The first player to get 3 of their marks in a row (horizontally, vertically, or diagonally) wins
5. If all 9 cells are filled and no player has won, the game is a draw (Cat's Game)

## Documentation Sections

- [Code Structure](code/structure.html): Details about the structure of the codebase
- [Usage Guide](code/usage.html): How to compile and run the program
- [Game Logic](code/game_logic.html): Explanation of the game's logic and algorithms
