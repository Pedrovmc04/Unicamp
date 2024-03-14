.section .text

.globl set_engine
set_engine:
    li a7,10
    ecall
    ret

.globl set_handbrake
set_handbrake:
    li a7,11
    ecall
    ret

.globl read_sensor_distance
read_sensor_distance:
    li a7,13
    ecall
    ret

.globl get_position
get_position:
    li a7,15
    ecall
    ret

.globl get_rotation
get_rotation:
    li a7,16
    ecall
    ret

.globl get_time
get_time:
    li a7,20
    ecall
    ret

.globl puts
puts:
    addi sp,sp,-8
    sw ra,0(sp)  #save return register
    1:
        lb t0,(a0)
        beqz t0,1f

        sw a0,4(sp)
        add a0,t0,zero
        call write_char
        lw a0,4(sp)
        
        addi a0,a0,1
        j 1b
    1:
    
    sw a0,4(sp)
    li a0,'\n'
    call write_char
    lw a0,4(sp)

    lw ra,0(sp)
    addi sp,sp,8
    ret

write_char:
    la t0,output_char
    sb a0,(t0) #carrego o byte
    li a0,'p'
    la a0,output_char #carrego o byte
    li a1,1    # size
    li a7,18   # syscall write_seral (18)
    ecall
    ret

.globl gets
gets:
    addi sp,sp,-12
    sw ra,0(sp)
    sw a0,4(sp)
    1:
        sw a0,8(sp)
        call read_char
        mv t0,a0
        lw a0,8(sp)

        li t1,'\n'
        beq t0,t1,1f

        sb t0,(a0)
        addi a0,a0,1
        j 1b
    1:
    
    sb zero,(a0)

    lw ra,0(sp)
    lw a0,4(sp)
    addi sp,sp,12
    
    ret

read_char:
    la a0, input_char
    li a1, 1
    li a7, 17 # syscall read_Serial (17)
    ecall
    lb a0, input_char
    ret

.globl atoi
atoi:
    li a3,0
    li t0,'0'
    li t1,'9'
    li t2,10
    li t3,'-'
    li t4,1
    addi t1,t1,1

    lb a1,(a0)
    beq a1,t3,2f
    j 1f
    2:
        addi a0,a0,1
        li t4,-1
    1:
        lb a1,(a0)
        beqz a1,1f
        addi a0,a0,1
        blt a1,t0,1b
        bge a1,t1,1b

        addi a1,a1,-'0'
        mul a3,a3,t2
        add a3,a3,a1
        j 1b
    1:
    mul a3,a3,t4

    mv a0,a3
    ret

.globl itoa
itoa:
    li t0,10 #Flag
    li t1,0 #Tamanho da String
    li t3,10 #

    bge a0,zero,1f
    bne a2,t0,1f


    li t0,-1
    mul a0,a0,t0 # Change to positive in base 10
    li t0,0

    1:
        remu t2,a0,a2   #Get the digit in base a2
        divu a0,a0,a2
        bge t2,t3,2f    #if digit >= 10
        addi t2,t2,'0'
        j 3f
    2:
        addi t2,t2,'a'
        addi t2,t2,-10
    3:
        sb t2,(a1)
        addi a1,a1,1
        addi t1,t1,1 # add a digit and size
        beqz a0,1f
        j 1b
    1:
        bnez t0,1f
        li t0,'-'
        sb t0,(a1)
        addi a1,a1,1
        addi t1,t1,1  
    1:
    sub a1,a1,t1
    mv a0,a1
    add a0,a0,t1
    sb zero,(a0)
    addi a0,a0,-1
    addi t1,t1,-1

    li t0,0
    1:
        bge t0,t1,1f
        lb t2,(a1)
        lb t3,(a0)
        sb t2,(a0)
        sb t3,(a1)

        addi a1,a1,1
        addi a0,a0,-1
        addi t0,t0,1
        addi t1,t1,-1
        
        j 1b
    1:

    sub a0,a0,t1

    ret

.globl approx_sqrt
approx_sqrt:
    li t0,2
    div t1,a0,t0
    1:
        beqz a1,1f
    
        div t2,a0,t1
        add t1,t1,t2
        div t1,t1,t0

        addi a1,a1,-1
        j 1b
    1:
        add a0,t1,zero

    ret

.globl get_distance
get_distance:
    #a0 = x1 # a3 = x2
    #a1 = y1 # a4 = y2
    #a2 = z1 # a5 = z2

    sub t0,a0,a3
    sub t1,a1,a4
    sub t2,a2,a5

    mul t0,t0,t0
    mul t1,t1,t1
    mul t2,t2,t2

    add t0,t0,t1
    add t0,t0,t2

    add a0,t0,zero
    li a1,15

    addi sp,sp,-4
    sw ra,(sp)
    call approx_sqrt
    lw ra,(sp)
    addi sp,sp,4

    ret

.globl strlen_custom
strlen_custom:
    li t0,0
    1:
        lb t1,(a0)
        beqz t1,1f
        addi t0,t0,1
        addi a0,a0,1
        j 1b
    1:
    
    mv a0,t0

    ret

.globl fill_and_pop
fill_and_pop:
    li t0,0
    li t1,28

    1:
        lw t2,(a0)
        sw t2,(a1)
        beq t0,t1,1f
        addi t0,t0,4
        addi a0,a0,4
        addi a1,a1,4
        j 1b
    1:
    lw a0,(a0)
    ret

.globl exit
exit:  
    li a7, 93
    ecall

.section .data
input_char: .byte 0 #buffer
output_char: .byte 0#buffer