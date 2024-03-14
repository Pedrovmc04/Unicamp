.text

read:
    addi sp,sp,-16 
    sw a0,0(sp)
    sw a1,4(sp)
    sw a2,8(sp)
    sw a7,12(sp)
    li a0, 0  # file descriptor = 0 (stdin)
    la a1, input_address #  buffer to write the data
    li a2, 1  # size (reads only 1 byte)
    li a7, 63 # syscall read (63)
    ecall
    lw a0,0(sp)
    lw a1,4(sp)
    lw a2,8(sp)
    lw a7,12(sp)
    addi sp,sp,16
    ret

.globl _start
_start:
    li t1,20
    li a2,0
    li t3,10
    li a5,' '
    li a6,'\n'

    1:
        beqz t1,write
        addi t1,t1,-1

        call read
        lb t2,input_address
        
        beq t2,a5,2f
        beq t2,a6,2f

        addi t2,t2,-'0'

        mul a2,a2,t3
        add a2,a2,t2
    
        j 1b
    
    2:
        la a1,output
        addi a1,a1,19
        sub a1,a1,t1
        sb a5,(a1)

        li t6,2
        li a3,0
        div a3,a2,t6
        
        li t4,10
    3:
        beqz t4,3f

        div t0,a2,a3
        add a3,a3,t0
        div a3,a3,t6

        addi t4,t4,-1
        j 3b
    3:
        li t5,4
        li a2,0
        add a2,a2,a3
    3:    
        rem t2,a2,t3
        div a2,a2,t3
        addi t2,t2,'0'
        
        addi a1,a1,-1
        sb t2,(a1)
        
        addi t5,t5,-1
        beqz t5,1b
        j 3b

    write:
        li a0, 1            # file descriptor = 1 (stdout)
        la a1, output
        sb a6,19(a1)
        li a2, 20           # size
        li a7, 64           # syscall write (64)
        ecall
        j exit

    exit:
        li a0, 0    
        li a7, 93
        ecall

.bss
input_address: .skip 0x20  # buffer
output: .skip 0x20

.data
string:  .asciz "Hello! It works!!!\n"