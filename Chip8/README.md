# Chip8 emulator

A custom chip8 emulator written in ANSI C for linux. There is not a working build for windows.

This project was created with the intent to learn more about low level program, and simulating hardware. 
This is in no wise perfect code though effort was put into making the code readable and efficent.

## build

Dependencies: SDL2 library for rendering and keyboard input. There are many guides for installing SDL2 so I will not include one here.

After cloning the repository, run make to build the project.

```bash
./chip8 <.ch8 binary file>
```