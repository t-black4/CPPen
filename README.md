Here’s a clear README explaining your OpenGL window project setup with GLFW and GLAD:

---

# OpenGL Window Example

This project creates a simple OpenGL window using **GLFW** for window and input management, and **GLAD** to load OpenGL functions.

---

## Project Structure

```
project/
├── main.cpp            # Main source file creating the OpenGL window
├── CMakeLists.txt      # Build configuration with CMake
└── external/
    └── glad/           # GLAD OpenGL loader files (include + src)
        ├── include/
        └── src/
```

---

## Dependencies

* **GLFW** — For creating windows and handling input
* **GLAD** — For loading OpenGL function pointers
* **OpenGL** — The graphics API provided by your GPU drivers

---

## Setup Instructions

1. **GLAD**

* Download GLAD from [https://glad.dav1d.de](https://glad.dav1d.de)
* Configure for OpenGL 3.3 Core, language C/C++
* Extract the generated `glad.zip` contents into `external/glad` directory

2. **GLFW**

* Install GLFW development files on Ubuntu:

```bash
sudo apt install libglfw3-dev
```

3. **Build**

Run these commands from the root of the project:

```bash
mkdir build
cd build
cmake ..
make
```

4. **Run**

Execute the compiled binary:

```bash
./OpenGLWindow
```

You should see a window with a teal background that resizes properly.

---

## How it Works

* `main.cpp` initializes GLFW and creates a window with an OpenGL 3.3 Core profile context.
* GLAD loads the OpenGL functions required for rendering.
* The framebuffer size callback updates the viewport on window resize.
* The render loop clears the window with a teal color and polls for events until you close the window.
* On exit, GLFW cleans up resources.

---

## CMake Details

* Defines C++17 standard.
* Builds a static GLAD library from the included source.
* Finds OpenGL and GLFW installed on your system.
* Links your executable to GLAD, GLFW, and OpenGL libraries.

---

## Next Steps

* Add shader compilation to render shapes.
* Implement text rendering with FreeType.
* Add input handling for interactivity.

---
