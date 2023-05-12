// symbol table with labels

(LOOP)
@i
D=M
@limit
D=D-M
@EXIT
D;JGT
@i
D=M
@sum
M=D+M
@i
M=M+1
@LOOP


(limit) 15
(sum) 0
(EXIT) 
