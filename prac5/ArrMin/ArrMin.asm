// Finds the smallest element in the array of length R2 whose first element is at RAM[R1] and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
@R1
D=M
@R2
D=D+M

// Set R0 to maximum value
@R0
M=-1

// Loop through array elements
(loop)
    // Check if end of array is reached
    @R2
    D=M
    @R1
    D=D-M
    @END
    D;JLE

    // Load element at current position
    @R1
    A=M
    D=M

    // Check if element is smaller than current smallest
    @R0
    D=D-M
    @SMALLER
    D;JLT

    // Element is not smaller, continue to next element
    @R1
    M=M+1
    @loop
    0;JMP

(SMALLER)
    // Update current smallest element
    @R0
    M=D

    // Move to next element
    @R1
    M=M+1
    @loop
    0;JMP

// End of array reached
(END)
@END
0;JMP