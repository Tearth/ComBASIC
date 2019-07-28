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

# Example application

#### BASIC code
```basic
0 REM Application generating random board every one second
5 REM
10 CLS
20 LET width = 120
30 LET height = 30
40 FOR y = 1 TO height - 1
50 FOR x = 1 TO width - 1
60 LET r = RND(1)
70 IF r = 1 THEN
80 PRINT "O";
90 ELSE
100 PRINT " ";
110 END IF
120 NEXT
130 PRINT
140 NEXT
150 WAIT 1000
160 GOTO 10
```

#### Compilator output
```
C:\Users\Pawel\Desktop\GitHub\ComBASIC\Test>ComBASIC -c -d -i plansza\plansza.bas -o plansza\output.asm
Starting compilation plansza\plansza.bas...
--------------------------------------------------------------
List of generated tokens:
[3 0] [0 REM] [2 Program] [2 generujacy] [2 co] [2 okreslony] [2 czas] [2 losowa] [2 plansze] [8 END_OF_INSTRUCTION]
[3 5] [0 REM] [8 END_OF_INSTRUCTION]
[3 10] [0 CLS] [8 END_OF_INSTRUCTION]
[3 20] [0 LET] [2 width] [6 =] [3 120] [8 END_OF_INSTRUCTION]
[3 30] [0 LET] [2 height] [6 =] [3 30] [8 END_OF_INSTRUCTION]
[3 40] [0 FOR] [2 y] [6 =] [3 1] [0 TO] [2 height] [6 -] [3 1] [8 END_OF_INSTRUCTION]
[3 50] [0 FOR] [2 x] [6 =] [3 1] [0 TO] [2 width] [6 -] [3 1] [8 END_OF_INSTRUCTION]
[3 60] [0 LET] [2 r] [6 =] [1 RND] [6 (] [3 1] [6 )] [8 END_OF_INSTRUCTION]
[3 70] [0 IF] [2 r] [6 =] [3 1] [0 THEN] [8 END_OF_INSTRUCTION]
[3 80] [0 PRINT] [4 O] [5 ;] [8 END_OF_INSTRUCTION]
[3 90] [0 ELSE] [8 END_OF_INSTRUCTION]
[3 100] [0 PRINT] [4  ] [5 ;] [8 END_OF_INSTRUCTION]
[3 110] [0 END IF] [8 END_OF_INSTRUCTION]
[3 120] [0 NEXT] [8 END_OF_INSTRUCTION]
[3 130] [0 PRINT] [8 END_OF_INSTRUCTION]
[3 140] [0 NEXT] [8 END_OF_INSTRUCTION]
[3 150] [0 WAIT] [3 1000] [8 END_OF_INSTRUCTION]
[3 160] [0 GOTO] [3 10] [8 END_OF_INSTRUCTION]
End of tokens list
120 30 1 height 1 - 1 width 1 - 1 RND r 1 = 1000 Generated abstract syntax tree:
38
   21 0
      29
   21 5
      29
   21 10
      3
   21 20
      20
         34 width
         12
            26 120
   21 30
      20
         34 height
         12
            26 30
   21 40
      13
         38
            34 y
            12
               26 1
         12
            32
               26 1
               34 height
         38
            21 50
               13
                  38
                     34 x
                     12
                        26 1
                  12
                     32
                        26 1
                        34 width
                  38
                     21 60
                        20
                           34 r
                           12
                              31
                                 26 1
                     21 70
                        17
                           12
                              9
                                 26 1
                                 34 r
                           38
                              21 80
                                 28
                                    34 var0
                                    24
                           38
                              21 100
                                 28
                                    34 var1
                                    24
            21 130
               28
   21 150
      35
         12
            26 1000
   21 160
      14
         34 10
End of abstract syntax tree
Symbol table:
0 width 0
0 height 0
0 y 0
0 x 0
0 r 0
1 var0 O
1 var1
End of symbol table
Compilation done!
```

#### Running exe:
![Example 1](https://i.imgur.com/onuflxF.png)