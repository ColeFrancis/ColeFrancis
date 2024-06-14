// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.

//R2=0
//n=R0
//LOOP:
//    if n=0 goto END
//    R2=R2+R1
//    n=n-1
//	  goto LOOP
//END:
//    goto END
	
	@R2
	M=0
	
	@R0
	D=M
	@n
	M=D
(LOOP)
	@n
	D=M
	@END
	D;JEQ
	
	@R1
	D=M
	@R2
	M=D+M
	
	@n
	M=M-1
	
	@LOOP
	0;JMP
	
(END)
	@END
	0;JMP

