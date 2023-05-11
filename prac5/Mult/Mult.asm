


// This file is based on part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: Mult.asm

// Multiplies R1 and R2 and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

@R0
M=0

// Jump into the first STEP if R2 > 0.
@R2
D=M
@STEP
D;JGT

// If it didn't jump, go to END.
@END
0;JMP

// Adds R1 to R2 and removes 1 from R0.
// If R0 is more than 0 we step again.
(STEP)
    // Get R0.
    @R0
    D=M

    // Add R1 to it.
    @R1
    D=D+M

    // And write the result back to R2.
    @R0
    M=D

    // Reduce R2 by 1.
    @R2
    D=M-1
    M=D

    // If R2 is still > 0 then loop.
    @STEP
    D;JGT

(END)
    @END
    0;JMP




