; ComBASIC input/output functions

section .bss
    iobuffer:    resb    128

section .text

extern GetStdHandle
extern WriteFile
extern ExitProcess
extern SetConsoleCursorPosition
extern GetConsoleScreenBufferInfo
extern FillConsoleOutputCharacterA
extern ReadConsoleA
extern GetTickCount
extern Sleep

_getstdinputhandle:
    push    ebp
    mov     ebp, esp

    ; HANDLE GetStdHandle(STD_INPUT_HANDLE)
    push    -10             ; STD_INPUT_HANDLE
    call    GetStdHandle
   
    mov     esp, ebp
    pop     ebp
    ret
    
_getstdoutputhandle:
    push    ebp
    mov     ebp, esp

    ; HANDLE GetStdHandle(STD_OUTPUT_HANDLE)
    push    -11             ; STD_OUTPUT_HANDLE
    call    GetStdHandle
   
    mov     esp, ebp
    pop     ebp
    ret

; char
_printchar:
    push    ebp
    mov     ebp, esp
    
    call    _getstdoutputhandle
    mov     ebx, eax    

    ; BOOL WriteFile(hstdOut, message, length, bytesWritten, overlapped)
    push    0               ; overlapped
    push    0               ; bytesWritten
    push    1               ; length
    lea     eax, [ebp+8]
    push    eax             ; message
    push    ebx             ; hStdOut
    call    WriteFile
    
    mov     esp, ebp
    pop     ebp
    ret     4
    
; number
_printnumber:
    push    ebp
    mov     ebp, esp
    
    call    _getstdoutputhandle
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
    ret     4
    
; message
; length
_printstring:
    push    ebp
    mov     ebp, esp

    call    _getstdoutputhandle
    mov     ebx, eax    

    ; BOOL WriteFile(hStdOut, message, length, bytesWritten, overlapped)
    push    0               ; overlapped
    push    0               ; bytesWritten
    mov     eax, [ebp+8]    
    push    eax             ; length
    mov     eax, [ebp+12]
    push    eax             ; message
    push    ebx             ; hStdOut
    call    WriteFile
    
    mov     esp, ebp
    pop     ebp
    ret     8

_readnumber:
    push    ebp
    mov     ebp, esp

    sub     esp, 4
    
    call    _getstdinputhandle
    mov     ebx, eax
    
    ;BOOL WINAPI ReadConsole(hConsoleInput, lpBuffer, nNumberOfCharsToRead, lpNumberOfCharsRead, pInputControl)
    push    0               ; pInputControl
    lea     eax, [ebp-4]
    push    eax             ; lpNumberOfCharsRead
    push    128             ; nNumberOfCharsToRead
    push    iobuffer        ; lpBuffer
    push    ebx             ; hConsoleInput
    call    ReadConsoleA
    
    ; pop digits count and sub end line chars
    pop     esi
    sub     esi, 3
    
    mov     ebx, iobuffer
    xor     eax, eax
    xor     edx, edx
    
_readnumber_loop:
    imul    eax, 10
    xor     ecx, ecx
    mov     cl, [ebx]
    
    cmp     ecx, '-'
    jne     _readnumber_add_number
    mov     edx, 1
    inc     ebx
    dec     esi
    jmp     _readnumber_loop
    
_readnumber_add_number:
    sub     ecx, '0'
    add     eax, ecx
    inc     ebx
    dec     esi
    
    cmp     esi, 0
    jge     _readnumber_loop
    
    cmp     edx, 1
    jne     _readnumber_end
    neg     eax
    
_readnumber_end: 
    mov     esp, ebp
    pop     ebp
    ret
    
; x
; y
_setcursorposition:
    push    ebp
    mov     ebp, esp
    
    call    _getstdoutputhandle
    mov     ebx, eax 
    
    mov     ax, [ebp+8]
    shl     eax, 16
    mov     ax, [ebp+12]
    
    ; BOOL SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition)
    push    eax                 ; hConsoleOutput
    push    ebx                 ; dwCursorPosition
    call    SetConsoleCursorPosition
    
    mov     esp, ebp
    pop     ebp
    ret     8
    
_clear:
    push    ebp
    mov     ebp, esp
    
    call    _getstdoutputhandle
    mov     ebx, eax
    
    sub     esp, 28
    
    ; BOOL GetConsoleScreenBufferInfo(hConsoleOutput, lpConsoleScreenBufferInfo)
    lea     eax, [ebp-24]
    push    eax                 ; hConsoleOutput
    push    ebx                 ; lpConsoleScreenBufferInfo
    call    GetConsoleScreenBufferInfo
    
    xor     eax, eax
    xor     ecx, ecx
    mov     ax, [ebp-6]
    mov     cx, [ebp-8]
    imul    ecx
    mov     edx, eax
    
    ; BOOL WINAPI FillConsoleOutputCharacter(hConsoleOutput, cCharacter, nLength, dwWriteCoord, lpNumberOfCharsWritten);
    lea     eax, [ebp-28]
    push    eax                 ; lpNumberOfCharsWritten
    push    0                   ; dwWriteCoord
    push    edx                 ; nLength
    push    ' '                 ; cCharacter
    push    ebx                 ; hConsoleOutput
    call    FillConsoleOutputCharacterA
    
    push    0
    push    0
    call    _setcursorposition
    
    mov     esp, ebp
    pop     ebp
    ret
    
_gettime:
    push    ebp
    mov     ebp, esp
    
	; DWORD GetTickCount(void)
    call    GetTickCount
    
    mov     esp, ebp
    pop     ebp
	ret

_wait:
	push    ebp
    mov     ebp, esp
    
	; VOID WINAPI Sleep(dwMilliseconds);
    call    Sleep
    
    mov     esp, ebp
    pop     ebp
	ret		4
    
_exit:
    push    ebp
    mov     ebp, esp
    
    ; VOID ExitProcess(0)
    push    0
    call    ExitProcess
    
    mov     esp, ebp
    pop     ebp
    ret