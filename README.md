# chipeu - Yet Another Chip-8 Interpreter 👾

A simple, clean, and kawaii Chip-8 interpreter written in C++! ✨ It's based on the original Chip-8-sama specification. (ﾉ◕ヮ◕)ﾉ*:･ﾟ✧

## What is Chip-8? 🤓

Chip-8 is an interpreted programming language, developed by Joseph Weisbecker in the mid-1970s on the COSMAC VIP and Telmac 1800 8-bit microcomputers. It was a simple way to create games and applications on these early systems. Today, writing a Chip-8 interpreter is a popular "hello, world!" project for anyone interested in learning about emulation!

## Features

* ✅ **Full Opcode Support:** Implements all 35 original Chip-8 opcodes.
* 🎨 **Graphics Rendering:** Uses the SDL2 library for simple and cross-platform windowing and graphics.
* 🔊 **Basic Sound:** Sound needs to be implemented :/ 
* ⌨️ **Keyboard Input:** Input still needs to be implemented :/

## Dependencies 🛠️

To build and run `chipeu`, you will need:
* A C++ compiler (g++, Clang, etc.)
* **SDL2:** A cross-platform development library for low-level access to audio, keyboard, mouse, and graphics hardware.

You can install SDL2 on your system using a package manager:
* **Debian / Linux Mint:** `sudo apt-get install libsdl2-dev`
* **Arch Linux:** `sudo pacman -S sdl2-compat`
* **macOS (with Homebrew):** `brew install sdl2`
* **Windows:** Download the development libraries from the [SDL website](https://www.libsdl.org/download-2.0.php) and configure your build environment.

## Building and Running 🚀

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/theroguevigilante/chipeu.git
    cd chipeu
    ```

2.  **Compile the source code:**
    Use make to compile the project, making sure to link against the SDL2 library.
    ```bash
    make all
    ```
    *(Note: You might need to change this command based on your project setup!)*

3.  **Run the interpreter:**
    Execute the compiled binary, passing the path to a Chip-8 ROM file as a command-line argument.
    ```bash
    ./chipeu path-to-your-rom.ch8
    ```
    Several public domain ROMs are available online for testing, such as `ibm.ch8` or `test_opcode.ch8`. Have fun!
    There are some test ROMs in the tests folder. Thanks to [Timendus](https://github.com/timendus)

## Controls 🎮

The original 16-key keypad will be mapped to a modern keyboard pretty soon.

## License 📜

This project is licensed under the AGPL License. See the `LICENSE` file for more details.
