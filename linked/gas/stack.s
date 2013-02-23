.section .data
stackTop:
        .int 0
output:
        .asciz "This is a test\n"

.section .bss
.lcomm linkedMemory, 100

.section .text
.globl main

main:
        movl    $1, %eax
        movl    $10, %ebx
        int     $0x80

