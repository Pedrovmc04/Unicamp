.text
read_num:
    addi sp,sp,-4
    sw ra,0(sp)

    li t1,10
    li t2,' '
    li t3,'\n'
    li t4,'\r'
    li a0,0
    1:
        call read    
        
        lb a1,input_address
        
        beq a1,t2,1f
        beq a1,t3,1f
        beq a1,t4,1b

        addi a1,a1,-'0'
        mul a0,a0,t1
        add a0,a0,a1
        
        j 1b
    1:
        lw ra,0(sp)
        addi sp,sp,4
        ret

read:
    addi sp,sp,-16 
    sw a0,0(sp)
    sw a1,4(sp)
    sw a2,8(sp)
    sw a7,12(sp)

    mv a0, s10  # file descriptor = 0 (stdin)
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

openfile:
    li a0, -100
    la a1, input_file
    li a2, 0
    li a3, 0
    li a7, 56
    ecall
    mv s10, a0
    ret

setCanvasSize:
    li a7, 2201
    ecall
    ret

setPixel:
    li a7, 2200
    ecall
    ret


.globl _start
_start:
    call openfile
    call read_num

    call read_num
    mv s0,a0        #Read W
    call read_num
    mv s1,a0        #Read H
    call read_num
    mv s2,a0        #Read A

    mv a0,s0
    mv a1,s1
    call setCanvasSize

    li t1,0
    1:
        li t0,0
        2:  
            call read
            lbu a2,input_address # Read a byte
            li t3,16843008
            mul a2,a2,t3    # 16843008*x
            addi a2,a2,255    # 16843008 + x + 255

            mv a0,t0
            mv a1,t1

            call setPixel

            addi t0,t0,1
            beq t0,s0,2f
            j 2b
        2:

        addi t1,t1,1
        beq t1,s1,1f
        j 1b
    1:

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
input_file: .asciz "image.pgm"