.text
.set STDOUT,0xFFFF0100
.set OUTPUT,0xFFFF0101
.set STDIN,0xFFFF0102
.set INPUT,0xFFFF0103

puts:
    addi sp,sp,-8
    sw ra,0(sp)  #save return register
    1:
        lb a1,(a0)
        beqz a1,1f

        sw a0,4(sp)
        addi a0,a1,0
        call write_char
        lw a0,4(sp)
        
        addi a0,a0,1
        j 1b
    1:
    
    sw a0,4(sp)
    addi a0,zero,'\n'
    call write_char
    lw a0,4(sp)

    lw ra,0(sp)
    addi sp,sp,8
    ret

write_char:
    li t0,OUTPUT
    sb a0,(t0)
    li t0,STDOUT
    li t1,1
    sb t1,(t0)
    1:
        lb t1,(t0)
        bnez t1,1b
    ret

gets:
    addi sp,sp,-12
    sw ra,0(sp)
    sw a0,4(sp)
    li t2,0
    1:
        sw a0,8(sp)
        call read_char
        mv t1,a0
        lw a0,8(sp)

        li t0,'\n'
        beq t1,t0,1f

        sb t1,(a0)
        addi a0,a0,1      
        addi t2,t2,1
        j 1b
    1:
    sb zero,(a0)
    lw ra,0(sp)
    lw a0,4(sp)
    addi sp,sp,12
    mv a1,t2
    ret

read_char:
    li t0,STDIN
    li t1,1
    sb t1,(t0)
    1:
        lb t1,(t0)
        bnez t1,1b
    li a0,INPUT
    lb a0,(a0)
    ret

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
        addi t2,t2,'A'
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


reverse:
    add a1,a0,a1
    addi a1,a1,-1

    1:
        bge a0,a1,1f
        lb t1,(a1)
        lb t0,(a0)
        sb t1,(a0)
        sb t0,(a1)

        addi a0,a0,1
        addi a1,a1,-1
        j 1b
    1:
    ret

separete:
    la t0,first_number
    la t1,operator
    la t2,second_number
    1:
        lb t3,(a0)
        li t4,' '
        sb t3,(t0)
        addi a0,a0,1
        addi t0,t0,1

        beqz t3,1f
        beq t3,t4,1f
        j 1b
    1:
        lb t3,(a0)
        li t4,' '
        sb t3,(t1)
        addi a0,a0,1
        addi t1,t1,1

        beqz t3,1f
        beq t3,t4,1f
        j 1b
    1:
        lb t3,(a0)
        li t4,' '
        sb t3,(t2)
        addi a0,a0,1
        addi t2,t2,1

        beqz t3,1f
        beq t3,t4,1f
        j 1b
    1:

    ret


.globl _start
_start:
    la a0,input_string
    call gets
    lb a0,input_string

    li t1,'1'
    li t2,'2'
    li t3,'3'
    li t4,'4'

    beq a0,t1,1f
    beq a0,t2,2f
    beq a0,t3,3f
    beq a0,t4,4f

    1:
        la a0,input_string
        call gets
        la a0,input_string
        call puts
        j exit
    2:
        la a0,input_string
        call gets
        la a0,input_string
        call reverse
        la a0,input_string
        call puts
        j exit
    3:
        la a0,input_string
        call gets
        la a0,input_string
        call atoi
        la a1,input_string
        li a2,16
        call itoa
        la a0,input_string
        call puts
        j exit
    4:
        la a0,input_string
        call gets
        la a0,input_string
        call separete
        la a0,first_number
        call atoi
        mv s0,a0
        la a0,second_number
        call atoi
        mv s1,a0

        li t1,'+'
        li t2,'-'
        li t3,'*'
        li t4,'/'
        lb a0,operator

        beq a0,t1,1f
        beq a0,t2,2f
        beq a0,t3,3f
        beq a0,t4,4f

        1:
            add a0,s0,s1
            j 5f
        2:
            sub a0,s0,s1
            j 5f
        3:
            mul a0,s0,s1
            j 5f
        4:
            div a0,s0,s1
        5:
            la a1,input_string
            li a2,10
            call itoa
            la a0,input_string
            call puts

    j exit

exit:
    li a0, 0    
    li a7, 93
    ecall

.data
input_char: .byte 0
input_string: .skip 30
first_number: .skip 20
second_number: .skip 20
operator: .skip 20
string:  .asciz "pedroo\0"