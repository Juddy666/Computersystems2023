// This file is based on part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: Mult.asm

// Multiplies R1 and R2 and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
@R1
D=M
@MULTLOOP
D;JLE
@R1
D=M
@NEGATE_R1
D;JLT
@R3
M=D
@MULTLOOP
@R2
D=M
@R4
M=D
@R0
M=0
(MULTLOOP)
@R4
D=M
@LSB
D=D&M
@SKIPADD
D;JEQ
@R1
D=M
@R0
D=D+M
@R0
M=D
(SKIPADD)
@R1
D=M
@SHIFT_R1
M=D
@R4
D=M
@SHIFT_R4
M=D
@COUNTER
MD=M-1
@MULT_LOOP
D;JGT
(END)
@END
0;JMP
(NEGATE_R1)
D=0
D-M
@R3
M=D
@MULT_LOOP

(LSB)
0000000000000001

(SHIFT_R1)
D=D>>1
@MULT_LOOP

(SHIFT_R4)
D=D>>1
@MULT_LOOP

(COUNTER)
0000000000000011