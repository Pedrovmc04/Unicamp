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

read_num:
    addi sp,sp,-4
    sw ra,0(sp)

    li t1,10
    li t2,' '
    li t3,'\n'
    li t4,'-'
    li t5,1
    li a0,0

    1:
        call read    
        
        lb a1,input_address
        
        beq a1,t2,3f
        beq a1,t3,3f
        bne a1,t4,2f
        li t5,-1
        j 1b
    2:
        addi a1,a1,-'0'
        mul a0,a0,t1
        add a0,a0,a1
        
        j 1b
    3:
        mul a0,a0,t5
        lw ra,0(sp)
        addi sp,sp,4
        ret

print_num:
    la a1,output
    li a2,0 #size
    li t6,0
    li t5,10
    bge a0,zero,1f 
    addi t6,t6,-1
    mul a0,a0,t6
    1:
        addi a1,a1,1
        addi a2,a2,1

        rem t0,a0,t5
        div a0,a0,t5
        addi t0,t0,'0'

        sb t0,(a1)

        beqz a0,1f
        j 1b
    1:
        beqz t6,1f
        li t0,'-'
        addi a1,a1,1
        addi a2,a2,1
        sb t0,(a1)
    1:
        addi a1,a1,1
        li t0,'\n'
        sb t0,(a1)

    2:
        la t0,output
        la t1,output
        add t1,t1,a2
    2:
        bge t0,t1,2f
        
        lb t2,(t0)
        lb t3,(t1)
        sb t2,(t1)
        sb t3,(t0)
        
        addi t0,t0,1
        addi t1,t1,-1
        j 2b
    2:
        addi sp,sp,-4
        sw ra,0(sp)

        call write
        
        lw ra,0(sp)
        addi sp,sp,4
        ret
        

search:
    li a0,0
    la a1,head_node

    1:
        beqz a1,1f

        lw t0,0(a1)
        lw t1,4(a1)

        add t2,t0,t1

        beq s0,t2,2f
        
        lw a1,8(a1)
        addi a0,a0,1
        j 1b
    1:
        li a0,-1
        ret
    2:
        ret

.globl _start
_start:
    call read_num
    mv s0,a0

    call search

    #li a0,-1235
    call print_num

    j exit

write:
    li a0, 1            # file descriptor = 1 (stdout)
    la a1, output
    li a2, 20           # size
    li a7, 64           # syscall write (64)
    ecall
    ret

exit:
    li a0, 0    
    li a7, 93
    ecall

.bss
input_address: .skip 0x20  # buffer
output: .skip 0x20

.data
string:  .asciz "Hello! It works!!!\n"