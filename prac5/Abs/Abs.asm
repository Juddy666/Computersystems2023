// Calculates the absolute value of R1 and stores the result in R0.
// (R0, R1 refer to RAM[0], and RAM[1], respectively.)

// Put your code here.


@R1
D=M //storeR1 in D

@ABS
M=D

@NEG
D;JLT //is D negative ?

@ABS
D=M //if D is not negative jump to ABS

@R0   
M=D //store in R0

(END)
@END //termintate
0;JMP

(NEG)
@ABS 
M=-M //Negate the Value of the temporary variable (ABS)

@ABS
D=M

@RO
M=D // store the two'complement in R0

(END)
@END
0;JMP
