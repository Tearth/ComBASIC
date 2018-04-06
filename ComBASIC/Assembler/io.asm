; ComBASIC input/output functions

extern GetStdHandle
extern WriteFile
extern ExitProcess
extern SetConsoleCursorPosition
extern GetConsoleScreenBufferInfo
extern FillConsoleOutputCharacterA

_getstdhandle:
    push    ebp
    mov     ebp, esp

    ; HANDLE GetStdHandle(STD_OUTPUT_HANDLE)
    push    -11
    call    GetStdHandle
   
    mov     esp, ebp
    pop     ebp
    ret

; char
_printchar:
    push    ebp
    mov     ebp, esp
    
    call    _getstdhandle
    mov     ebx, eax    

    ; BOOL WriteFile(hstdOut, message, length, 0, 0);
    push    0
    push    0
    push    1
    lea     eax, [ebp+8]
    push    eax
    push    ebx
    call    WriteFile
    
    mov     esp, ebp
    pop     ebp
    ret     4
    
; number
_printnumber:
    push    ebp
    mov     ebp, esp
    
    call    _getstdhandle
    mov     ebx, eax
    
    ; check if the specified number is negative
    mov     eax, [ebp+8]
    and     eax, 0x80000000
    cmp     eax, 0
    
    jz      _init_numtostr
    
    mov     eax, [ebp+8]
    neg     eax
    mov     [ebp+8], eax
    
    push    '-'
    call    _printchar

_init_numtostr:
    xor     ecx, ecx
    xor     esi, esi

    mov     eax, [ebp+8]
    
_numtostr_loop:
    xor     edx, edx
    
    mov     ecx, 10
    idiv    ecx
    push    edx
    
    inc     esi
    
    cmp     eax, 0
    jnz     _numtostr_loop
    
_printdigit_loop:
    pop     eax
    add     eax, '0'
    push    eax
    call    _printchar
    
    dec     esi
    cmp     esi, 0
    jnz     _printdigit_loop
    
    mov     esp, ebp
    pop     ebp
    ret		4
    
; message
; length
_printstring:
    push    ebp
    mov     ebp, esp

    call    _getstdhandle
    mov     ebx, eax    

    ; BOOL WriteFile(hstdOut, message, length, 0, 0);
    push    0
    push    0
    mov     eax, [ebp+8]
    push    eax
    mov     eax, [ebp+12]
    push    eax
    push    ebx
    call    WriteFile
    
    mov     esp, ebp
    pop     ebp
    ret     8

; x
; y
_setcursorposition:
    push    ebp
    mov     ebp, esp
    
    call    _getstdhandle
    mov     ebx, eax 
    
    mov     ax, [ebp+8]
    shl     eax, 16
    mov     ax, [ebp+12]
    
    ; BOOL SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition)
    push    eax
    push    ebx  
    call    SetConsoleCursorPosition
    
    mov     esp, ebp
    pop     ebp
    ret     8
    
_clear:
    push    ebp
    mov     ebp, esp
    
    call    _getstdhandle
    mov     ebx, eax
    
    sub     esp, 28
    
    ; BOOL GetConsoleScreenBufferInfo(hConsoleOutput, lpConsoleScreenBufferInfo)
    lea     eax, [ebp-24]
    push    eax
    push    ebx
    call    GetConsoleScreenBufferInfo
    
    xor     eax, eax
    xor     ecx, ecx
    mov     ax, [ebp-6]
    mov     cx, [ebp-8]
    imul    ecx
    mov     edx, eax
    
    ; BOOL WINAPI FillConsoleOutputCharacter(hConsoleOutput, cCharacter, nLength, dwWriteCoord, lpNumberOfCharsWritten);
    lea     eax, [ebp-28]
    push    eax
    push    0
    push    edx
    push    ' '
    push    ebx
    call    FillConsoleOutputCharacterA
    
    push    0
    push    0
    call    _setcursorposition
    
    mov     esp, ebp
    pop     ebp
    ret
    
_exit:
    push    ebp
    mov     ebp, esp
    
    ; VOID ExitProcess(0)
    push    0
    call    ExitProcess
    
    mov     esp, ebp
    pop     ebp
    ret