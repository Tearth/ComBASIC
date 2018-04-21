# ComBASIC

The simple BASIC compiler written in plain C without any external libraries. It takes BASIC file as input and generates Assembly output code which can be assembled by the NASM/MASM and linked with GoLink or some similar software to the executable file.

# Example usage

```bat
ComBASIC -c -d -i helloworld.bas -o helloworld.asm
nasm -f win32 helloworld.asm -o helloworld.obj
golink /console /entry _main helloworld.obj kernel32.dll user32.dll
helloworld.exe
pause
```

**Available options:**
  * -h - displays help
  * -c - runs compilation (requires -i and -o)
  * -d - displays debug info during compilation (like tokens list, AST tree, ...)
  * -i - specifies input BASIC file
  * -o - specifies output ASM file

# Compilation process overview

![compilation process](https://noqw8w.bn.files.1drv.com/y4mMwUAQZsMHK0KO23r6aAd9y0H2ESzhOsUUcnZENJSjPeVLEVdpPy1K0KduUBrh_7ZKsonRIvXwyHIS_MKY5v7-2UAo6AD0SJ1Mis2jb6H4YVBUypWwA7A917ewUg501ZUrYvTVJBKll5_N8BwRtBNOdYvBcODz8cqHtvt5BT3RqQoH0tk9eodGVpIs9fJ_nqHsMbG1Qfipw5TIBqr4kHI8w/compilation.png)

# Instructions

| Name        | Description | Usage |
| ------------- | ------- | ---- |
| CLS          | Clears the console and moves cursor position to the begin. | CLS  |
| END          | Ends program and exits the console. | END  |
| REM          | Comment, skipped during compilation. | REM any tokens until the new line chars  |
| LET          | Assigns an expression to the specified variable. | LET variable = expression  |
| WHILE ... WEND          | Loops the instruction block until the specified expression is true. | WHILE expression<br>&nbsp;&nbsp;&nbsp;&nbsp;instructions block<br>WEND  |
| FOR ... TO ... STEP ... NEXT          | Loops the instruction block until the expression is less than condition (step is greater than 0) or the expression is greater than the condition (if step is less than 0). Default step is 1. | FOR variable = expression TO expression<br>&nbsp;&nbsp;&nbsp;&nbsp;instructions block<br>NEXT<br><br>FOR variable = expression TO expression STEP expression<br>&nbsp;&nbsp;&nbsp;&nbsp;instructions block<br>NEXT|
| IF ... THEN ... ELSE ... END IF         | Just conditional statement. | IF expression THEN<br>&nbsp;&nbsp;&nbsp;&nbsp;instructions block<br>END IF<br><br>IF expression THEN<br>&nbsp;&nbsp;&nbsp;&nbsp;instructions block<br>ELSE<br>&nbsp;&nbsp;&nbsp;&nbsp;instructions block<br>END IF |
| GOTO          | Jumps to the specified line. | GOTO line_number  |
| GOSUB ... RETURN          | Stores the current instruction address onto stack and jumps to the specified line. When enters the RETURN, resumes program at the line after GOSUB instruction using the address from the stack. | GOSUB line_number<br>...<br>instructions block<br>RETURN  |
| PRINT          | Prints the specified content (string or expression) to the console.| PRINT "Hello "; 1+3*4, variable, " World!"; |
| INPUT          | Reads numbers from the console to the specified variables. | INPUT "Prompt message"; variable1, variable2, variable3 |
| WAIT          | Pauses the program for the specified milliseconds number. | WAIT expression |

# Operators

| Symbols        | Priority |
| ------------- | ---- |
| * /          | 80  |
| MOD        | 60  |
| + -          | 50  |
| <> < <= > >= =        | 30  |
| AND         | 20  |
| OR          | 15  |
| ( )         | 10  |

# Functions


| Name        | Description |
| ----------- | ---- |
| ABS(value)  | Returns absolute value of the expression passed in the argument.  |
| RND(max)    | Returns random integer number in the range from 0 to *max*  |
| TIME()      | Returns current ticks count from OS start (note that there is no 64 bit variable here, so returned value may not be accurate, but enough to calculate short time intervals).  |