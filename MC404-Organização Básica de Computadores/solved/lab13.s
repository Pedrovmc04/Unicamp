.section .text
.align 2

.set GPT_BASE,0xFFFF0100
.set MDI_BASE,0xFFFF0300

.globl play_note
play_note:
    # a0 = Channel | a1 = InstrumentID | a2 = Note | a3 = Velocity | a4 = duration
    li t0,MDI_BASE

    sh a1,2(t0)
    sb a2,4(t0)
    sb a3,5(t0)
    sh a4,6(t0)
    sh a0,(t0)

    ret

external_isr:
    lw a0,_system_time
    addi a0,a0,100
    sw a0,_system_time,t0

    ret

main_isr:
    # Salvar o contexto
    csrrw sp, mscratch, sp # Troca sp com mscratch
    addi sp, sp, -64 # Aloca espaço na pilha da ISR
    sw a0,(sp)
    sw a1,4(sp)
    sw a2,8(sp)
    sw a3,12(sp)
    sw a4,16(sp)
    sw t0,20(sp)
    sw t1,24(sp)
    sw t2,28(sp)

    # Trata a interrupção
    csrr a1, mcause # lê a causa da interrupção
    bgez a1, handle_exc # Verifica se é exceção ou int.
    andi a1, a1, 0x3f # Isola EXCCODE
    li a2, 11 # a2 = interrupção externa
    bne a1, a2, otherInt
    jal external_isr

    handle_exc:
    otherInt:

    li a0,GPT_BASE
    li t0,100
    sw t0,8(a0) # Genarate a interruption in 100 ms

    # Recupera o contexto
    lw t2,28(sp)
    lw t1,24(sp)
    lw t0,20(sp)
    lw a4,16(sp)
    lw a3,12(sp)
    lw a2,8(sp)
    lw a1,4(sp)
    lw a0,(sp)
    addi sp, sp, 64 # Desaloca espaço da pilha da ISR
    csrrw sp, mscratch, sp # Troca sp com mscratch novamente
    mret # Retorna da interrupção

.globl _start
_start:
    # Configura mscratch com o topo da pilha das ISRs.
    la t0, isr_stack_end # t0 <= base da pilha
    csrw mscratch, t0 # mscratch <= t0

    la t0, main_isr # Carrega o endereço da main_isr
    csrw mtvec, t0 # em mtvec

    # Habilita Interrupções Externas
    csrr t1, mie # Seta o bit 11 (MEIE)
    li t2, 0x800 # do registrador mie
    or t1, t1, t2
    csrw mie, t1
    # Habilita Interrupções Global
    csrr t1, mstatus # Seta o bit 3 (MIE)
    ori t1, t1, 0x8 # do registrador mstatus
    csrw mstatus, t1

    #SET A GPT
    li a0,GPT_BASE
    li t0,100
    sw t0,8(a0) # Genarate a interruption in 100 ms


    j main

.section .bss
.align 4
isr_stack: # Final da pilha das ISRs
.skip 1024 # Aloca 1024 bytes para a pilha
isr_stack_end: # Base da pilha das ISRs

.section .data
.globl _system_time
_system_time: .word 0