#LAB-10-A-B
.text
.globl puts
puts:
    addi sp,sp,-8
    sw ra,0(sp)  #save return register
    1:
        lb a1,(a0)
        beqz a1,1f

        sw a0,4(sp)
        add a0,a1,zero
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
    addi sp,sp,-4
    sb a0,0(sp)
    mv a1,sp
    
    li a0, 1            # file descriptor = 1 (stdout)
    li a2, 1           # size
    li a7, 64           # syscall write (64)
    ecall
    
    lb a0,4(sp)
    addi sp,sp,4
    ret

.globl gets
gets:
    addi sp,sp,-12
    sw ra,0(sp)
    sw a0,4(sp)
    li t0,'\n'

    1:
        sw a0,8(sp)
        call read_char
        lw a0,8(sp)
        lb a1,input_char
        sb a1,(a0)
        addi a0,a0,1
        beq a1,t0,1f
        j 1b
    1:
    sb zero,(a0)
    lw ra,0(sp)
    lw a0,4(sp)
    addi sp,sp,12
    ret

read_char:
    li a0, 0  # file descriptor = 0 (stdin)
    la a1, input_char
    li a2, 1  # size (reads only 1 byte)
    li a7, 63 # syscall read (63)
    ecall
    ret


.globl exit
exit:  
    li a7, 93
    ecall

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

.globl linked_list_search
linked_list_search:
    li t3,0
    1:
        beqz a0,1f

        lw t0,0(a0)
        lw t1,4(a0)

        add t2,t0,t1

        beq a1,t2,2f
        
        lw a0,8(a0)
        addi t3,t3,1
        j 1b
    1:
        li t3,-1
    2:
        mv a0,t3
        ret

.globl recursive_tree_search
recursive_tree_search:
    bnez a0,1f
    li a0,0
    ret
    
    1:
        lw t0,(a0)
        bne t0,a1,1f
        #la a0,string
        #call puts
        li a0,1
        ret
    1:
        #Search Left
        addi sp,sp,-8
        sw ra,0(sp)
        sw a0,4(sp)
        lw a0,4(a0)
        call recursive_tree_search
        mv t0,a0
        lw a0,4(sp)
        lw ra,0(sp)
        addi sp,sp,8
        #Search Right
        addi sp,sp,-12
        sw ra,0(sp)
        sw t0,4(sp)
        sw a0,8(sp)
        lw a0,8(a0)
        call recursive_tree_search
        mv t1,a0
        lw a0,8(sp)
        lw t0,4(sp)
        lw ra,0(sp)
        addi sp,sp,12

    1:
        beqz t0,1f
        mv a0,t0
        addi a0,a0,1
        ret
    1:
        beqz t1,1f
        mv a0,t1
        addi a0,a0,1
        ret
    1:
        li a0,0
        ret

.data
input_char: .byte 0 #buffer