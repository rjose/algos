%include 'system.inc'

section .data
Hello   db      'Hello, World', 0Ah
hbytes  equ     $ - hello

section .text

global  _start
_start:

push    dword hbytes
push    dword hello
push    dword stdout
sys.write

push    dword 0
sys.exit
