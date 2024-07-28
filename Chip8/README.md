# Chip8 emulator

A custom chip8 emulator written in ANSI C for linux. There is not a working build for windows.

The SDL2 library was used to handle the rendering and the keyboard inputs to greatly simplify the code.

This project was created with the intent to learn more about low level program, and simulating hardware and was designed to be simple and clean.
This is in no wise perfect code though effort was put into making the code readable and efficent.

## build

Dependencies: SDL2 library for rendering and keyboard input. There are many guides for installing SDL2 so I will not include one here.

After cloning the repository, run make to build the project.

Use the following command to run the emulator:
```bash
./chip8 <.ch8 binary file>
```

## Final notes

This project has been finished and I do not intend to return to add features, except to fix any bugs