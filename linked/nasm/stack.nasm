%include 'system.inc'

section .data
        hello           db      'Hello, World', 0Ah
        hbytes          equ     $ - hello
        NUM_NODES       equ     100
        top             db      -1     ; offset into linkmem


section .text
global  _start
_start:
        push    dword hbytes
        push    dword hello
        push    dword stdout
        sys.write

        call init               ; Initialize the linked memory

        ; Push something onto our stack
        push    byte 0x22       ; arg to pushval
        call    pushval
        add     esp, 4          ; 'pop' arg to pushval

        push    byte 0x33       ; arg to pushval
        call    pushval
        add     esp, 4          ; 'pop' arg to pushval

        push    byte 0x44       ; arg to pushval
        call    pushval
        add     esp, 4          ; 'pop' arg to pushval

        call    popval
        add     esp, 4

        push    byte 0x11       ; arg to pushval
        call    pushval
        add     esp, 4          ; 'pop' arg to pushval

        ; Exit
        push    dword 0
        sys.exit

pushval:
        mov     eax, [avail]
        ; TODO: Check for overflow

        ; P <= avail
        mov     ecx, linkmem
        movzx   edx, byte [eax+1]   ; The second byte contains the offset into the next avail memory
        add     ecx, edx            ; ecx now points to the new avail memory
        mov     [avail], ecx        ; |avail| now points to the next avail memory

        ; INFO(P) <- value
        mov     dl, [esp+4]
        mov     [eax], dl

        ; LINK(P) <- T
        mov     dl, [top]
        mov     [eax+1], dl

        ; T <- P
        sub     eax, linkmem
        mov     [top], byte al
        ret


popval:
        pop     ebx             ; Store return address

        ; P <- T
        movzx   eax, byte [top]         ; eax holds the offset into linkmem of the top of the stack
        ; TODO: Check for underflow

        ; T <- LINK(P)
        mov     ecx, linkmem
        add     ecx, eax
        mov     dx, word [ecx]
        mov     [top], dh


        ; Push INFO(P)
        movzx   edx, byte dl
        push    edx

        ; AVAIL <= P
        mov     edx, [avail]    ; Store offset of avail into LINK(P)
        sub     edx, linkmem
        mov     [ecx+1], byte edx
        mov     [avail], ecx    ; Point avail to P

        push    ebx             ; Push return address back onto stack
        ret

; This goes through linkmem and links the nodes together.
init:
        push ebx
        push ecx

        mov     ebx, linkmem
        mov     [avail], ebx
        
        mov     ecx, 1          ; ecx holds index into linkmem
l1:     mov     ebx, linkmem    ; 
        add     ebx, ecx        ; Compute address to write offset into

        mov     [ebx], ecx      ; Write offset into node
        inc     BYTE [ebx]
        add     ecx, 2
        cmp     ecx, 2*NUM_NODES-1
        jne     l1

        pop ecx
        pop ebx
        ret

section .bss
        linkmem         resw    NUM_NODES
        linksize        equ     $ - linkmem
        values          resb    2
        avail           resw    1
