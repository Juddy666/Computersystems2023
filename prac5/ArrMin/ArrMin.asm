// Finds the smallest element in the array of length R2 whose first element is at RAM[R1] and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)


// Put your code here.
@R1
D=M-1
@R2
M=M+D

@32767
D=A
@R0
M=D

(LOOP)
@R1
D=M
@R2
D=D-M
@END
D;JGT
@R1
A=M
D=M
@ELEMPOS
D;JGE
@ELEMNEG
(UPDATE)
@R1
A=M
D=M
@R0
M=D
(SKIP)
@R1
M=M+1
@LOOP
0;JMP

(END)
@END
0;JMP

(ELEMNEG)
@R0
D=M
@R0NEG
D;JLT
@SKIP
0;JMP

(ELEMPOS)
@R0
D=M
@R0POS
D;JGE
@SKIP
0;JMP

(R0POS)
@R1
A=M
D=M
@R0
D=D-M
@SKIP
D;JGE
@UPDATE
0;JMP

(R0NEG)
@R1
A=M
D=M
@R0
D=D-M
@SKIP
D;JLT
@UPDATE
0;JMP

(SKIP)
@R1
M=M+1
@LOOP
0;JMP