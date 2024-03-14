.text
.align 4

.set CAR_BASE,0xFFFF0100
.set STEERING_WHELL,0xFFFF0120
.set ENGINE,0xFFFF0121

int_handler:
    # Salvar o contexto
    csrrw sp, mscratch, sp # Troca sp com mscratch
    addi sp, sp, -64 # Aloca espaço na pilha da ISR
    sw a1,0(sp)
    sw a2,4(sp)
    sw a3,8(sp)
    sw a4,12(sp)
    sw t0,16(sp)
    sw t1,20(sp)
    sw t2,24(sp)

    ###### Syscall and Interrupts handler ######

    # <= Implement your syscall handler here 
    li t0,10
    beq a7,t0,Syscall_set_engine_and_steering
    li t0,11
    beq a7,t0,Syscall_set_handbrake
    li t0,12
    beq a7,t0,Syscall_read_sensors
    li t0,15
    beq a7,t0,Syscall_read_sensors
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

        li t0,STEERING_WHELL
        sb a1,(t0)

        li t0,ENGINE
        sb a0,(t0)

        li a0,0
        j end
        1:
            li a0,-1
            j end
    Syscall_set_handbrake:
        j end
    Syscall_read_sensors:
        j end
    Syscall_get_position:
        j end


    end:

    csrr t0, mepc  # load return address (address of 
                    # the instruction that invoked the syscall)
    addi t0, t0, 4 # adds 4 to the return address (to return after ecall) 
    csrw mepc, t0  # stores the return address back on mepc

    # Recupera o contexto
    lw t2,24(sp)
    lw t1,20(sp)
    lw t0,16(sp)
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

    la t0, user_main # Loads the user software
    csrw mepc, t0 # entry point into mepc

    mret

.globl control_logic
control_logic:
  # implement your control logic here, using only the defined syscalls
    li a0,1
    li a1,-15
    li a7,10
    ecall

.section .bss
.align 4
isr_stack: # Final da pilha das ISRs
.skip 1024 # Aloca 1024 bytes para a pilha
isr_stack_end: # Base da pilha das ISRs

.section .data