# Cheesboard-Playground

Cheesboard-Playground is a C++ and OpenGL project designed as an interactive virtual chessboard. Users can navigate the chessboard using arrow keys, and the project incorporates multiple views and windows managed with ImGUI. This project serves both as a learning platform for OpenGL and as a template for future advanced graphics projects.

## Features

- **Interactive Chessboard Navigation**: Move across the chessboard using arrow keys.
- **Multiple Views and Windows**: Leverage ImGUI to create and manage multiple windows and views.
- **Customizable Framework**: Designed to be extensible for advanced OpenGL graphics projects.

## Objectives

1. **Learn OpenGL**: Understand the basics of OpenGL, rendering, shaders, and buffer management.
2. **Explore ImGUI**: Integrate and utilize ImGUI for GUI elements and window management.
3. **Build a Template**: Create a reusable framework for future graphics projects.

## Getting Started

### Prerequisites

- A C++17 or later compiler (e.g., GCC, Clang, MSVC)
- Premake5 (for project generation)
- OpenGL 3.3 or later
- GLFW (for window management)
- ImGUI (for graphical user interface)

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/Cheesboard-Playground.git
   cd Cheesboard-Playground
   ```

2. Generate project files with Premake5:
   ```bash
   premake5 gmake2  # Replace `gmake2` with your desired Premake action
   ```

3. Build the project:
   ```bash
   make  # Or use the appropriate build command for your platform
   ```

4. Run the executable:
   ```bash
   ./CheesboardPlayground
   ```

## Project Structure

```
Cheesboard-Playground/
├── src/                # Source code for the application
├── include/            # Header files
├── shaders/            # Shader programs
├── assets/             # Additional resources (textures, models, etc.)
├── vendor/        # External dependencies (e.g., ImGUI, GLFW)
├── premake5.lua        # Premake build configuration
└── README.md           # Project documentation
```

## Usage

- **Navigation**: Use the arrow keys to move across the chessboard.
- **GUI Controls**: Access different views and settings through ImGUI windows.

## Planned Features

- Enhanced camera controls (zoom, rotate, pan).
- Dynamic lighting and shadow effects.
- Support for importing and visualizing 3D models.

## Acknowledgments

- [GLFW](https://www.glfw.org/) - OpenGL Window and Input Library
- [ImGUI](https://github.com/ocornut/imgui) - Graphical User Interface Library
- [LearnOpenGL](https://learnopengl.com/) - OpenGL Learning Resource
