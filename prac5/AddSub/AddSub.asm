// Calculates R1 + R2 - R3 and stores the result in R0.
// (R0, R1, R2, R3 refer to RAM[0], RAM[1], RAM[2], and RAM[3], respectively.)

@R1
D=M //store in d
@R2 
D=D+M // add D(a) + M(b)
@R3
D=D-M //sub M(c) from D
@R0
M=D