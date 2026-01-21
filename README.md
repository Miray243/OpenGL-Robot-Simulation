# OpenGL Virtual Exhibition Hall

This project is an interactive virtual exhibition hall application developed using **C++** and **OpenGL (GLUT)**. Users can explore a 3D environment, control a hierarchical robot model, and interact with dynamic lighting systems.

## 🎥 Features

* **Hierarchical Robot Modeling:** A fully animated robot with independently moving wheels, arm, and scanner head.
* **Camera System:**
    * **Follow Mode:** The camera automatically tracks the robot from behind.
    * **Free Mode:** Users can freely navigate the scene using keyboard controls.
* **Dynamic Lighting:** Real-time spotlighting with toggle functionality and visual beam effects.
* **3D Environment:** A textured room environment containing exhibition assets.
* **3D Model Support:** The project includes 3D assets in **.glb** format (e.g., `12.glb`, `smh1.glb`).

## 🎮 Controls

The application uses a keyboard-based control system for navigation and interaction.

### 🤖 Robot Controls
| Key | Action |
| :--- | :--- |
| **W** | Move Robot Forward |
| **S** | Move Robot Backward |
| **A** | Turn Robot Left |
| **D** | Turn Robot Right |
| **SPACE** | Toggle Laser Scanner Animation |

### 📷 Camera Controls
| Key | Action | Description |
| :--- | :--- | :--- |
| **F** | Toggle Camera Mode | Switch between **Follow Mode** & **Free Mode** |
| **Arrow Up** | Look Up | *Only in Free Mode* |
| **Arrow Down** | Look Down | *Only in Free Mode* |
| **Arrow Left** | Look Left | *Only in Free Mode* |
| **Arrow Right** | Look Right | *Only in Free Mode* |

### 💡 Lighting & System
| Key | Action |
| :--- | :--- |
| **L** | Toggle Spotlights On/Off |
| **ESC** | Exit Application |

## 🛠️ Requirements & Build

### Dependencies
* **C++ Compiler** (GCC / Clang / MSVC)
* **OpenGL Libraries:** FreeGLUT, GL, GLU
* **Helper Libraries:** `tiny_obj_loader.h` (included for model loading logic)

### ⚠️ Note on 3D Models
The project assets are provided in **.glb** format (e.g., `12.glb`, `231.glb`). The current source code implements `tiny_obj_loader`, which is designed for `.obj` files. To ensure models render correctly in the scene, you may need to:
1.  Convert the `.glb` files to `.obj` format using an external tool (like Blender or online converters).
2.  Or update the model loading logic to support binary glTF formats.

### How to Compile (Linux/macOS)
```bash
g++ *.cpp -o virtual_gallery -lGL -lGLU -lglut
How to Run
Ensure the executable and the 3D asset files are in the same directory, then run:

Bash

./virtual_gallery
