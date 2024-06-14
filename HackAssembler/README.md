# Assembler for Hack machine language

This was made as part of a project for the Nand to Tetris course, where one learns to design and build their own microprocessor using HDL and simulations.

All c source files, a makefile, and an example assembly code file named Mult.asm are included in this repository

## Use

Compile the code using the makefile or simply by hand

Make sure the .asm file containing your Hack Assembly code is in the same directory as the compiled program

Run the program in a terminal, with the full file name as the first command line parameter, and the name of your target file as the second.

## Details

Two debugging modes can be activated in the source code by defining the DEBUG_FORMATTER and DEBUG_PREPROCESSOR macros in the beginning of the HackAssembler.c file.

The resulting output of the assembler is formatted as strings of 1s and 0s in the output file.