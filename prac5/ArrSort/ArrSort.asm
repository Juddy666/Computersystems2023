// Sorts the array of length R2 whose first element is at RAM[R1] in ascending order in place. Sets R0 to True (-1) when complete.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

@SP
M=256

@LOOPA
D=0
@R1
M=M-1
@R2
D=M
@LOOPB
D;JLE
@R1
D=M
@R1
A=A-1
D=M-D
@SKIPSWAP
D;JGE
@R1
A=A+1
D=M
@R1
A=A-1
M=D
D=-1
(SKIPSWAP)
@R1
A=A-1
@LOOPB
D;JNE
D;JEQ
@SP
AM=M-1
@RO
M=-1
(END)