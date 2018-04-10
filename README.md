# ComBASIC

The simple BASIC compiler written in plain C without any external libraries.

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
| FOR ... TO ... NEXT          | FOR variable = value TO expression<br>&nbsp;&nbsp;&nbsp;&nbsp;instructions block<br>NEXT  |
| IF ... THEN ... ELSE ... END IF          | IF expression THEN<br>&nbsp;&nbsp;&nbsp;&nbsp;instructions block<br>ELSE<br>&nbsp;&nbsp;&nbsp;&nbsp;instructions block<br>END IF |
| GOTO          | GOTO line_number  |
| PRINT          | PRINT „String with new line”<br>PRINT „String without new line”;<br>PRINT expression<br>PRINT expression; |
| INPUT          | INPUT „Prompt message”; variable<br>INPUT „Prompt message”, variable |

# Operators

| Symbols        | Priority |
| ------------- | ---- |
| (, )          | 80  |
| *, /          | 60  |
| MOD          | 50  |
| +, -         | 30  |
| <>, <, <=, >, >=, =         | 20  |
| AND          | 15  |
| OR         | 10  |

