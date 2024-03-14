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

read_position:
    li t1,10
    li t2,' '
    li t3,'\n'
    li a0,0

    addi sp,sp,-4
    sw ra,0(sp)

    call read
    
    lw ra,0(sp)
    addi sp,sp,4
    
    lb t4,input_address
    addi t4,t4,-'-'
    1:
        addi sp,sp,-4
        sw ra,0(sp)
        
        call read    
        
        lw ra,0(sp)
        addi sp,sp,4
        
        lb a1,input_address
        
        beq a1,t2,1f
        beq a1,t3,1f
        
        addi a1,a1,-'0'
        mul a0,a0,t1
        add a0,a0,a1
        
        j 1b
    1:
        beqz t4,2f
        ret
    2:
        li t5,-1
        mul a0,a0,t5
        ret

read_time:
    addi sp,sp,-8
    sw ra,0(sp)
    sw a1,4(sp)

    li t1,10
    li t2,' '
    li t3,'\n'
    li a0,0
    1:
        call read    
        
        lb a1,input_address
        
        beq a1,t2,1f
        beq a1,t3,1f
        
        addi a1,a1,-'0'
        mul a0,a0,t1
        add a0,a0,a1
        
        j 1b
    1:
        lw ra,0(sp)
        lw a1,4(sp)
        addi sp,sp,8
        ret

print_num:
    add t1,zero,a0
    la a1,output+4
    li t6,0
    li t5,4
    li t4,10
    bge t1,zero,1f 
    addi t6,t6,-1
    mul t1,t1,t6
    
    1:
        rem t0,t1,t4
        div t1,t1,t4
        addi t0,t0,'0'

        sb t0,(a1)
        addi a1,a1,-1

        add t5,t5,-1
        beqz t5,1f
        j 1b
    1:
        la a1,output
        beqz t6,1f
        li t0,'-'
        sb t0,0(a1)
        j 2f
    1:
        li t0,'+'
        sb t0,0(a1)
    2:
        sb a6,5(a1)

        addi sp,sp,-4
        sw ra,0(sp)

        call write
        
        lw ra,0(sp)
        addi sp,sp,4
        ret

sqrt:
    addi sp,sp,-16
    sw a1,0(sp)
    sw a2,4(sp)
    sw t0,8(sp)
    sw t1,12(sp)

    li t0,2
    div a1,a0,t0
    li t1,21
    1:
        beqz t1,1f
    
        div a2,a0,a1
        add a1,a1,a2
        div a1,a1,t0

        addi t1,t1,-1
        j 1b
    1:
        add a0,a1,zero
        lw a1,0(sp)
        lw a2,4(sp)
        lw t0,8(sp)
        lw t1,12(sp)
        addi sp,sp,-1
        ret

distance:
    addi sp,sp,-4
    sw ra,0(sp)

    li t6,10
    li t5,3

    call read_time
    add a1,a0,zero # T-a
    call read_time
    add a2,a0,zero # T-b
    call read_time
    add a3,a0,zero # T-c
    call read_time
    add a4,a0,zero # T-r

    sub a1,a4,a1
    sub a2,a4,a2
    sub a3,a4,a3
    
    mul a1,a1,t5
    div a1,a1,t6

    mul a2,a2,t5
    div a2,a2,t6

    mul a3,a3,t5
    div a3,a3,t6

    lw ra,0(sp)
    addi sp,sp,4
    ret
    

.globl _start
_start:
    call read_position
    add s0,a0,zero # Y-b
    call read_position
    add s1,a0,zero # X-c

    call distance
    add s2,a1,zero # dist(a)
    add s3,a2,zero # dist(b)
    add s4,a3,zero # dist(c)

    # li a6,' '
    # add a0,s2,zero
    # call print_num
    # add a0,s3,zero
    # call print_num
    # li a6,'\n'
    # add a0,s4,zero
    # call print_num

    #Check Y coordinate

    mul t0,s2,s2
    mul t1,s0,s0
    mul t2,s3,s3

    add t0,t0,t1
    sub t0,t0,t2

    li t2,2
    mul t2,t2,s0
    rem t3,t0,t2
    div t0,t0,t2

    add s5,t0,zero # Y

    #Check X coordinate

    mul t0,s2,s2
    mul t1,s5,s5
    sub a0,t0,t1
    call sqrt
    add a1,zero,a0 # X1
    sub a2,zero,a0 # X2

    mul t5,s4,s4 # dist(c)^2
    mul t4,s5,s5 # (Y)^2
    
    sub t2,a1,s1
    mul t2,t2,t2 # (x1-Xb)^2
    add t2,t2,t4
    sub t2,t2,t5
    bgt t2,zero,1f
    sub t2,zero,t2
    1:
    sub t3,a2,s1
    mul t3,t3,t3 # (x2-Xb)^2
    add t3,t3,t4
    sub t3,t3,t5
    bgt t3,zero,1f
    sub t3,zero,t3
    1:
    
    blt t2,t3,1f
    add s6,zero,a2
    j 2f
    1:
    add s6,zero,a1
    2:

    add a0,s6,zero
    li a6,' '
    call print_num
    add a0,s5,zero
    li a6,'\n'
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