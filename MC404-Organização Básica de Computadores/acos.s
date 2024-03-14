.text
.align 4

.set CAR_BASE,0xFFFF0300
.set SERIAL_PORT,0xFFFF0500
.set GPT_BASE,0xFFFF0100

int_handler:
    # Salvar o contexto
    csrrw sp, mscratch, sp # Troca sp com mscratch
    addi sp, sp, -64 # Aloca espaço na pilha da ISR
    sw a1,0(sp)
    sw a2,4(sp)
    sw a3,8(sp)
    sw a4,12(sp)
    sw a5,16(sp)
    sw a6,20(sp)
    sw t0,24(sp)
    sw t1,28(sp)
    sw t2,32(sp)
    sw t3,36(sp)
    sw t4,40(sp)

    ###### Syscall and Interrupts handler ######

    # <= Implement your syscall handler here 
    li t0,10
    beq a7,t0,Syscall_set_engine_and_steering
    li t0,11
    beq a7,t0,Syscall_set_handbrake
    li t0,12
    beq a7,t0,Syscall_read_sensors
    li t0,13
    beq a7,t0,Syscall_read_sensor_distance
    li t0,15
    beq a7,t0,Syscall_get_position
    li t0,16
    beq a7,t0,Syscall_get_rotation
    li t0,17
    beq a7,t0,Syscall_read_serial
    li t0,18
    beq a7,t0,Syscall_write_seral
    li t0,20
    beq a7,t0,Syscall_get_systime
    
    j end
    Syscall_set_engine_and_steering:
        li t0,-1
        li t1,2
        blt a0,t0,1f
        bge a0,t1,1f

        li t0,-127
        li t1,128
        blt a1,t0,1f
        bge a1,t1,1f

        li t0,CAR_BASE
        sb a1,0x20(t0)
        sb a0,0x21(t0)

        li a0,0
        j end
        1:
            li a0,-1
            j end
    Syscall_set_handbrake:
        li t0,CAR_BASE
        sb a0,0x22(t0)
        j end
    Syscall_read_sensors:
        li t0,CAR_BASE
        li t1,1
        sb t1,1(t0)

        1:
            lb t1,1(t0)
            beqz t1,1f
            j 1b
        1:
        
        addi t0,t0,0x24
        li t2,256

        2:
            beqz t2,2f
            lbu t1,(t0)
            sb t1,(a0)
            addi a0,a0,1
            addi t0,t0,1
            addi t2,t2,-1
            j 2b
        2:
        j end
    Syscall_read_sensor_distance:
        li t0,CAR_BASE
        li t1,1
        sb t1,2(t0)
        
        1:
            lb t1,2(t0)
            beqz t1,1f
            j 1b
        1:
        lw a0,28(t0)
        j end
    Syscall_get_position:
        li t0,CAR_BASE
        li t1,1
        sb t1,(t0)

        1:
            lb t1,(t0)
            beqz t1,1f
            j 1b
        1:

        lw t1,0x10(t0)
        sw t1,(a0)
        lw t1,0x14(t0)
        sw t1,(a1)
        lw t1,0x18(t0)
        sw t1,(a2)
        j end
    Syscall_get_rotation:
        li t0,CAR_BASE
        li t1,1
        sb t1,(t0)

        1:
            lb t1,(t0)
            beqz t1,1f
            j 1b
        1:
        lw t1,0x4(t0)
        sw t1,(a0)
        lw t1,0x8(t0)
        sw t1,(a1)
        lw t1,0xC(t0)
        sw t1,(a2)
        j end
    Syscall_read_serial:
        li t2,0
        1:
        beq a1,t2,1f
        li t0,SERIAL_PORT
        li t1,1
        sb t1,2(t0)
        
        2:
            lb t1,2(t0)
            beqz t1,2f
            j 2b
        2:
        
        lb t1,3(t0)
        sb t1,(a0)

        beqz t1,1f

        addi a0,a0,1
        addi t2,t2,1

        j 1b
        1:
        mv a0,t2
        j end
    Syscall_write_seral:
        li t2,0
        1:
        beq a1,t2,1f
        li t0,SERIAL_PORT
        
        lb t1,(a0)
        sb t1,1(t0)
        
        li t1,1
        sb t1,(t0)

        2:
            lb t1,(t0)
            bnez t1,2b

        addi t2,t2,1
        beq a1,t2,1f
        addi a0,a0,1
        j 1b
        1:
        j end
    Syscall_get_systime:
        li t0,GPT_BASE
        li t1,1
        sb t1,(t0)
        1:
            lb t1,(t0)
            bnez t1,1b

        lw a0,4(t0)
        j end
    end:

    csrr t0, mepc  # load return address (address of 
                    # the instruction that invoked the syscall)
    addi t0, t0, 4 # adds 4 to the return address (to return after ecall) 
    csrw mepc, t0  # stores the return address back on mepc

    # Recupera o contexto
    lw t4,40(sp)
    lw t3,36(sp)
    lw t2,32(sp)
    lw t1,28(sp)
    lw t0,24(sp)
    lw a6,20(sp)
    lw a5,16(sp)
    lw a4,12(sp)
    lw a3,8(sp)
    lw a2,4(sp)
    lw a1,0(sp)
    addi sp, sp, 64 # Desaloca espaço da pilha da ISR
    csrrw sp, mscratch, sp # Troca sp com mscratch novamente
    mret           # Recover remaining context (pc <- mepc)
  

.globl _start
_start:
    la t0, isr_stack_end # t0 <= base da pilha
    csrw mscratch, t0 # mscratch <= t0

    la t0, int_handler  # Load the address of the routine that will handle interrupts
    csrw mtvec, t0      # (and syscalls) on the register MTVEC to set
                        # the interrupt array.

    # Write here the code to change to user mode and call the function 
    # user_main (defined in another file). Remember to initialize
    # the user stack so that your program can use it.

    csrr t1, mstatus # Update the mstatus.MPP
    li t2, ~0x1800 # field (bits 11 and 12)
    and t1, t1, t2 # with value 00 (U-mode)
    csrw mstatus, t1

    la t0, main # Loads the user software
    csrw mepc, t0 # entry point into mepc

    li sp, 0x07FFFFFC

    mret

.globl control_logic
control_logic:
  # implement your control logic here, using only the defined syscalls


.section .bss
.align 4
isr_stack: # Final da pilha das ISRs
.skip 1024 # Aloca 1024 bytes para a pilha
isr_stack_end: # Base da pilha das ISRs

.section .data
test: .skip 256