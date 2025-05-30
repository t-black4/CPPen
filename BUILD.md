---

## 1. Install C++ Compiler and Build Tools

```bash
sudo apt update
sudo apt install build-essential
```

---

## 2. Install Required Libraries

### OpenGL development files

```bash
sudo apt install libgl1-mesa-dev libglu1-mesa-dev
```

### pkg-config tool

```bash
sudo apt install pkg-config
```

### GLFW library

```bash
sudo apt install libglfw3-dev
```

---

## 3. Build Your Project

```bash
mkdir build
cd build
cmake ..
make
```

---
