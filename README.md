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
  • Positional correction to prevent sinking  
- **World Boundaries**  
  • Precise ball-wall collision detection  
  • Bouncing off walls with configurable energy loss
- **Multi-Threaded Simulation**  
  • Physics loop (60 Hz) on a background thread  
  • Thread safety by using `std::mutex` and `std::atomic`  
- **Interactive Drag & Throw**  
  • Click and drag balls with mouse  
  • Computes a “throw” velocity on release  
  • Momentum transfer on drag-collision  
- **Real-Time Rendering**  
  • GPU-accelerated 2D drawing via SFML (OpenGL backend)  
  • Frame-rate limited to 60 FPS (For efficency)
- **On-Screen Diagnostics**  
  • Live velocity readouts for each ball  
- **Configurable Parameters**  
  • Mass, radius, gravity, restitution coefficients (energy loss), world size  
- **Easy Build**  
  • Single Makefile (`make release`) with `-O3 -std=c++2b`  
  • Cross-platform SFML dependency
- **Fashion**
  • Blue and Maize Balls for an optimal user viewing experience

## Installation

1. Clone the repository:
   ```sh
   git clone 
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
│── Ball.h             # Declaration of the Ball class (position, velocity, integration)
│── Ball.cpp           # Ball class implementation (force/impulse application & Euler integrator)
│── Vector2.h          # 2D vector math declarations (operators, dot, normalize, etc.)
│── Vector2.cpp        # 2D vector math implementations
│── Physics.h          # Physics engine interface (gravity, timestep, world bounds)
│── Physics.cpp        # Physics engine implementation (apply forces, integrate, wall‐bounce)
│── Collisions.h       # Collision API (detect & resolve ball–ball collisions)
│── Collisions.cpp     # Collision implementation (impulse resolution, positional correction)
│── main.cpp           # Entry point: threading, input handling, SFML rendering, drag/throw
│── Makefile           # Build script (g++ flags, SFML include/libs, ‘make release’ target)
│── README.md          # Project overview, features, build instructions, usage guide

```

## Authors
- Jason Majoros