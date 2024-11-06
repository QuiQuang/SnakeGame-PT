# Snake Game

## Introduction
This project is a **Snake Game** built in **C++** and runs in the **console**. It is a classic game where the player controls a snake that must eat food to grow longer while avoiding collisions with walls and its own body. With each piece of food eaten, the snake grows longer. Once the player eats **three pieces of food**, they advance to the next level, where the game becomes slightly more challenging.

## Key Features
- **Console-based Gameplay:** Simple graphics that work in any console.
- **Level Progression:** The player advances to a new level after eating three pieces of food.
- **Increasing Difficulty:** Each new level increases the game’s speed, adding more challenge.
- **Score Tracking:** Points are awarded for each piece of food eaten, and the total score is displayed at the end of each level.
- **Game Over Conditions:** The game ends when the snake collides with a wall or itself.

## System Requirements
- **C++ Compiler** (such as **g++** or **MSVC**)
- Console with support for **ANSI escape codes** (optional, for better visual effects)

## How to Play
1. **Run the Game:** Compile and execute the game in your C++ environment.
2. **Controls:**
   - Use arrow keys to control the snake’s direction.
   - The snake will continue moving in the last direction it was heading until a new direction is input.
3. **Objective:** Eat food pieces to grow longer and earn points.
   - After eating three pieces of food, the player progresses to the next level.
   - With each new level, the game speed increases.
4. **End of Game:** The game ends when the snake collides with a wall or its own body. At this point, the final score is displayed.

## Installation and Compilation
1. Clone or download the project repository.
2. Open a terminal in the project directory.
3. Compile the code using a C++ compiler:
   ```bash
   Snake_Game.sln
