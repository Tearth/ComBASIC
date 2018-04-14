# ComBASIC

The simple BASIC compiler written in plain C without any external libraries. It takes BASIC file as input and generates Assembly output code which can be assembled by the NASM/MASM and linked by the GoLink or some similar software to exe.

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

| Name        | Usage |
| ------------- | ---- |
| CLS          | CLS  |
| END          | END  |
| REM          | REM any tokens until the new line chars  |
| LET          | LET variable = expression  |
| WHILE ... WEND          | WHILE expression<br>&nbsp;&nbsp;&nbsp;&nbsp;instructions block<br>WEND  |
| FOR ... TO ... STEP ... NEXT          | FOR variable = expression TO expression<br>&nbsp;&nbsp;&nbsp;&nbsp;instructions block<br>NEXT<br><br>FOR variable = expression TO expression STEP expression<br>&nbsp;&nbsp;&nbsp;&nbsp;instructions block<br>NEXT|
| IF ... THEN ... ELSE ... END IF          | IF expression THEN<br>&nbsp;&nbsp;&nbsp;&nbsp;instructions block<br>END IF<br><br>IF expression THEN<br>&nbsp;&nbsp;&nbsp;&nbsp;instructions block<br>ELSE<br>&nbsp;&nbsp;&nbsp;&nbsp;instructions block<br>END IF |
| GOTO          | GOTO line_number  |
| GOSUB ... RETURN          | GOSUB line_number<br>...<br>instructions block<br>RETURN  |
| PRINT          | PRINT "Hello "; 1+3*4, variable, " World!"; |
| INPUT          | INPUT "Prompt message"; variable1, variable2, variable3 |

# Operators

| Symbols        | Priority |
| ------------- | ---- |
| *, /          | 80  |
| MOD        | 60  |
| +, -          | 50  |
| <>, <, <=, >, >=, =        | 30  |
| AND         | 20  |
| OR          | 15  |
| (, )         | 10  |

