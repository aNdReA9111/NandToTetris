    @0
    D=M
    D;JLE 
    M=D
    @SCREEN
    D=A
    M=D
(LOOP)
A=M
M=-1
D=M
@32
D=D+A
M=D
MD=M-1
D;JGT
(INFINITE_LOOP)
0;JMP
