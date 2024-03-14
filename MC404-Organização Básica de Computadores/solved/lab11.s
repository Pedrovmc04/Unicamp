.text
.set STEERING_WHELL,0xFFFF0120
.set ENGINE,0xFFFF0121


.globl _start
_start:
    li t0,-15
    li a0,STEERING_WHELL
    sb t0,(a0)
    1:
        li t0,1
        li a0,ENGINE
        sb t0,(a0)

        j 1b

    j exit

exit:
    li a0, 0    
    li a7, 93
    ecall

.data
string:  .asciz "Hello! It works!!!\n"
