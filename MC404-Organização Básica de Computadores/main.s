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