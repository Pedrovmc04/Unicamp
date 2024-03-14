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
    la a2,output
    add a2,a2,a1
    add a3,a1,zero
    li t4,10

    li t0,'\n'
    sb t0,(a2)
    addi a2,a2,-1

    1:
        rem t0,a0,t4
        div a0,a0,t4
        addi t0,t0,'0'

        sb t0,(a2)
        
        add a1,a1,-1
        addi a2,a2,-1
        beqz a1,2f
        j 1b
    2:
        addi sp,sp,-4
        sw ra,0(sp)

        add a2,a3,zero
        add a2,a2,1
        call write
        
        lw ra,0(sp)
        addi sp,sp,4
        ret

encode:
    li a2,10

    rem t0,a0,a2 #d4
    div a0,a0,a2
    
    rem t1,a0,a2 #d3
    div a0,a0,a2

    rem t2,a0,a2 #d2
    div a0,a0,a2

    rem t3,a0,a2 # d1
    div a0,a0,a2
    
    xor t4,t3,t2 # P1
    xor t4,t0,t4

    xor t5,t3,t1 # P2
    xor t5,t5,t0

    xor t6,t2,t1 # P3
    xor t6,t6,t0

    add a0,a0,t4
    mul a0,a0,a2
    add a0,a0,t5
    mul a0,a0,a2
    add a0,a0,t3
    mul a0,a0,a2
    add a0,a0,t6
    mul a0,a0,a2
    add a0,a0,t2
    mul a0,a0,a2
    add a0,a0,t1
    mul a0,a0,a2
    add a0,a0,t0

    ret

decode:
    li a2,10
    rem t0,a0,a2 # d4
    div a0,a0,a2
    rem t1,a0,a2 # d3
    div a0,a0,a2
    rem t2,a0,a2 # d2
    div a0,a0,a2
    div a0,a0,a2
    rem t3,a0,a2 # d1

    li a0,0
    add a0,a0,t3
    mul a0,a0,a2
    add a0,a0,t2
    mul a0,a0,a2
    add a0,a0,t1
    mul a0,a0,a2
    add a0,a0,t0

    ret

.globl _start
_start:
    call read_num 
    add s0,a0,zero # A
    call read_num
    add s1,a0,zero # B

    add a0,s0,zero
    call encode
    add s2,a0,zero # Encoded A

    add a0,s1,zero
    call decode
    add s3,a0,zero # Decoded B

    add a0,s3,zero
    call encode
    add s4,a0,zero # Encoded B

    li s5,0
    beq s4,s1,1f
    addi s5,s5,1
    1:

    li a1,7
    add a0,s2,zero
    call print_num

    li a1,4
    add a0,s3,zero
    call print_num

    li a1,1
    add a0,s5,zero
    call print_num

    j exit
write:
    li a0, 1            # file descriptor = 1 (stdout)
    la a1, output       # size
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