// This file is based on part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: Mult.asm

// Multiplies R1 and R2 and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
@R1 
D=M //R1
@R0
M=0 //result

(LOOP)
@R2 
D;JEQ //exit if R2=0
@R0
M=M+D // add R1 to result
@R2
M=M-1 // Decrement R2
@LOOP
0;JMP

