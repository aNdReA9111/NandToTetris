// Initialize Stack Pointer (SP)
@256
D=A
@SP
M=D
(SimpleFunction.test)
0
@0
D=A
@SP
M=M+1
A=M-1
M=D
@0
D=A
@SP
M=M+1
A=M-1
M=D
@LCL
D=M
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
@LCL
D=M
@1
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
@SP
MD=M-1
A=D
D=M
A=A-1
M=M+D
@SP
A=M-1
M=!M
@ARG
D=M
@0
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
@SP
MD=M-1
A=D
D=M
A=A-1
M=M+D
@ARG
D=M
@1
A=D+A
D=M
@SP
M=M+1
A=M-1
M=D
@SP
MD=M-1
A=D
D=M
A=A-1
M=M-D
@LCL
D=M
@R14
M=D
@5
A=D-A
D=M
@R15
M=D
@ARG
D=M
@R13
M=D
@SP
AM=M-1
D=M
@R13
A=M
M=D
@ARG
D=M+1
@SP
M=D
@R14
D=M
@1
A=D-A
D=M
@THAT
M=D
@R14
D=M
@2
A=D-A
D=M
@THIS
M=D
@R14
D=M
@3
A=D-A
D=M
@ARG
M=D
@R14
D=M
@4
A=D-A
D=M
@LCL
M=D
@R15
A=M
0;JMP