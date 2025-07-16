# Multi-Threaded 2D Physics Engine

## Overview
This is a multi-threaded 2D physics engine in C++. It was built using Newtonian physics concepts—applying F = ma to move bodies under gravitational forces, resolving 2D ball-ball and ball-wall collisions using change in momentum (impulse), and integrating motion with a fixed‐timestep Euler integrator. Physics runs in its own thread, while rendering and input happen on the main thread.

## Features
- **Newtonian Mechanics**  
  • Gravity
  • Forces and mass-based acceleration  
- **2D Ball Collisions**  
  • Precise ball-ball collision detection  
  • Impulse resolution with energy loss (inelastic collisions)
- **World Boundaries**  
  • Precise ball-wall collision detection with positional correction
  • Bouncing off walls with configurable energy loss
- **Multi-Threaded Simulation**  
  • Physics loop (60 Hz) on a background thread  
  • Thread safety by using `std::mutex` and `std::atomic`  
- **Interactive Drag & Throw**  
  • Click and drag balls with the mouse  
  • Throw velocity is calculated from the mouse's movement while dragging
- **Real-Time Rendering**  
  • GPU-accelerated 2D drawing via SFML (OpenGL backend)  
  • Frame-rate limited to 60 FPS for efficiency
- **On-Screen Diagnostics**  
  • Live velocity readouts for each ball  
- **Configurable Parameters**  
  • Mass, radius, gravity, restitution coefficients (energy loss), world size
- **Modern C++ Optimizations**
  • Header-only vector math and collision libraries for maximum inlining
  • `constexpr` and `inline` used for compile-time calculations and reduced overhead
- **Easy Build**  
  • Single Makefile (`make release`) with `-O3 -std=c++2b`
  • Cross-platform SFML dependency
- **Fashion**
  • Blue and Maize Balls for an optimal user viewing experience
  • A third green ball was added only to show the increase in performance (Go Blue!)


## Installation

1. Clone the repository:
   ```sh
   git clone https://github.com/JasonCodesC/Physics-Engine.git
   ```

2. Navigate to the repository folder:
   ```sh
   cd <your-repo-path>
   ```

3. Install the required dependencies (Make sure you are compiling with C++23):
   ```sh
   Copy and run in the terminal: $ brew install sfml pkg-config make 
   ```

5. Start the Engine:
   ```sh
   make release; ./phys_sim
   ```

## Project Structure
```
/project-root
│── Ball.h             # Ball API
│── Ball.cpp           # Ball class implementation
│── Vector2.h          # Header-only 2D vector math library
│── Physics.h          # Physics engine API
│── Physics.cpp        # Physics engine implementation
│── Collisions.h       # Header-only collision detection and resolution library
│── main.cpp           # Entry point: threading, input handling, SFML rendering, drag/throw
│── Makefile           # Makefile for compiling
│── README.md          # Project overview, features, build instructions, usage guide

```

## V1
V1 is a clanky physics engine, it is multithreaded and runs at 60 fps but the collisions feel wrong. The collisions dont feel hard, the balls almost seem to go through each other for a split second and due to that the force calculations are wrong.

## V2
V2 runs very smooth. I added better error checking by using [[nodiscard]] and fixed some logic. I used constexpr in lots of places to make as many calculations happen at compile time as possible, as every millisecond counts. And all of the constexpr functions are implicitly inlined resulting in greater optimization. Other functions that couldn't benefit from constexpr now have the inline keyword, resulting in a huge performance boost due to the code being inlined at compile time so we no longer need to use branch instructions nearly as frequently.

## Authors
- Jason Majoros

# V1 
Completion April 2025
# V2 
Completion July 2025