# CPPen
A lightweight C++ GUI text editor for fast and simple editing.



---

## 🔧 **Phase 1: Project Setup**

### 1. **Choose a GUI Framework**

* Select: `Qt`, `wxWidgets`, `ImGui`, `GTK`, etc.
* Install libraries and set up the environment for your OS (e.g., install Qt Creator for Qt).

### 2. **Set Up Version Control**

* Initialize a `git` repository.
* Create `.gitignore` for build files and IDE configs.

### 3. **Project Structure**

* Create folders: `src/`, `include/`, `resources/`, `build/`.
* Create a base `main.cpp` with a minimal GUI window.

---

## 🧱 **Phase 2: Core GUI Layout**

### 4. **Window Setup**

* Create the main application window.
* Set title, size, and basic styling.

### 5. **Text Area Widget**

* Add a multi-line editable text widget (e.g., `QPlainTextEdit` or `wxTextCtrl`).
* Connect it to the main layout.

### 6. **Menu Bar**

* Add menus: `File`, `Edit`, `View`, `Help`.
* Populate with placeholders:

  * File: New, Open, Save, Save As, Exit
  * Edit: Undo, Redo, Cut, Copy, Paste, Select All
  * View: Toggle Word Wrap, Show Line Numbers (optional)
  * Help: About

---

## 🧠 **Phase 3: Core Functionality**

### 7. **File Operations**

* Implement New, Open, Save, Save As:

  * Open file dialog
  * Read/write from file
  * Handle unsaved changes

### 8. **Basic Edit Actions**

* Hook up cut, copy, paste, undo, redo.
* Keyboard shortcuts (Ctrl+S, Ctrl+O, etc.)

### 9. **Status Bar**

* Add a status bar showing cursor position, file name, and modification state.

---

## ✨ **Phase 4: Enhancements**

### 10. **Syntax Highlighting (Optional)**

* Create a basic lexer/parser.
* Highlight keywords, strings, comments, etc. using `QSyntaxHighlighter` (Qt) or similar.

### 11. **Line Numbers (Optional)**

* Create a line number margin.
* Sync it with scrolling in the text area.

### 12. **Search & Replace**

* Add a search bar or dialog.
* Support case-sensitive search, whole word, etc.

---

## 🗃️ **Phase 5: Configuration & Settings**

### 13. **Preferences Dialog**

* Theme selection (light/dark)
* Font and font size
* Word wrap toggle

### 14. **Settings Persistence**

* Save preferences to a config file (e.g., JSON, INI).
* Load settings on startup.

---

## 🚀 **Phase 6: Polish and Package**

### 15. **Custom Icons & UI Polish**

* Add icons to menu and buttons.
* Apply consistent styling (via QSS or CSS-like system if supported).

### 16. **Error Handling & Validation**

* Handle file read/write errors, unsaved changes, etc.

### 17. **Build System**

* Use CMake or your IDE’s build system to automate builds.
* Add release/debug builds.

### 18. **Cross-Platform Support (Optional)**

* Test on Linux, Windows, macOS.
* Add platform-specific adjustments if needed.

---

## 📦 **Phase 7: Deployment**

### 19. **Package Application**

* Use deployment tools: `windeployqt` (Qt) or installer creator.
* Bundle dependencies as needed.

### 20. **Create README and Documentation**

* Add build instructions
* Add usage examples and keyboard shortcuts

### 21. **Create Release Tags**

* Tag versions in Git
* Upload binaries (if public)
g for this project?
2. Do you want to include plugins, themes, or scripting support in the future?
3. Will this be a code editor (with syntax highlighting), or plain text only?
