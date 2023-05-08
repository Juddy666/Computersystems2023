// Finds the smallest element in the array of length R2 whose first element is at RAM[R1] and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
@R1
D=M
@R0
M=D

//R3 to the length

@R2
D=M
@R3
M=D

(LOOP)

@R3
D=M
@END
D;JEQ

@R1
D=M
@R4
M=D

@R0
D=M
@R4
D=D-M
@MIN
D;JGT

(MIN)
@R4
D=M
@R0
M=D
@R1
D=M
@1
A=A+1
D=D+A
@R1
M=D
@R3
M=M-1

@LOOP
0;JMP

(END)
@END
0;JMP