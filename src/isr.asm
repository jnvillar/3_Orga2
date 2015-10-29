; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; definicion de rutinas de atencion de interrupciones

%include "imprimir.mac"

BITS 32

sched_tarea_offset:     dd 0x00
sched_tarea_selector:   dw 0x00

;; PIC
extern fin_intr_pic1

;; Sched
extern sched_atender_tick
extern sched_tarea_actual

extern print
extern game_atender_tick
extern fin_intr_pic1
;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;
 
exception0 db     'Divide Error', 0
exception1 db     'RESERVED', 0
exception2 db     'N MI Interrupt', 0
exception3 db     'Breakpoint', 0
exception4 db     'Overflow', 0
exception5 db     'BOUND Range Exceeded', 0
exception6 db     'Invalid Opcode', 0
exception7 db     'Device Not Available', 0
exception8 db     'Double Fault', 0
exception9 db     'Coprocessor Segment Overrun', 0
exception10 db     'Invalid TSS', 0
exception11 db     'Segment Not Present', 0
exception12 db     'Stack-Segment Fault', 0
exception13 db     'General Protection', 0
exception14 db     'Page Fault', 0
exception15 db     'RESERVED', 0
exception16 db     'Floating-Point Error', 0
exception17 db     'Alignment Check', 0
exception18 db     'Machine Check', 0
exception19 db     'SIMD Floating-Point Exception', 0


exception32 db     0
exception33 db     0


%macro ISR 1
global _isr%1

_isr%1:
    push eax
    mov al, %1
    cmp al, 0x20
    jl .internas
    jge .externas

    .internas:
        mov eax, %1
        push 0xf
        push 0
        push 0
        push exception%1
        call print
        sub esp, 4
        sub esp, 4
        sub esp, 4
        sub esp, 4
        jmp $

    .externas:
        call fin_intr_pic1
        call game_atender_tick
        pop eax
        iret

%endmacro

;;
;; Datos
;; -------------------------------------------------------------------------- ;;
; Scheduler

;;
;; Rutina de atención de las EXCEPCIONES
;; 

ISR 0
ISR 1
ISR 2
ISR 3
ISR 4
ISR 5
ISR 6
ISR 7
ISR 8
ISR 9
ISR 10
ISR 11
ISR 12
ISR 13
ISR 14
ISR 15
ISR 16
ISR 17
ISR 18
ISR 19
ISR 32
ISR 33

;;--------------------------------------------------------------------------


;;
;; Rutina de atención del RELOJ
;; 


    



;;------------------------------------------------------------------------- 

;;
;; Rutina de atención del TECLADO
;; 



 


;;------------------------------------------------------------------------ 

;;
;; Rutinas de atención de las SYSCALLS
;;----------------------------------------------------------------------- ;;

