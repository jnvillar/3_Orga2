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
extern screen_actualizar_reloj_global
extern imprim
extern game_perro_actual
extern game_perro_mover
extern game_perro_cavar
extern game_perro_olfatear
extern game_atender_tick()
extern sched_atender_tick()

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
    mov eax, %1
    push 0xf
    push 0
    push 0
    push exception%1
    call print
    add esp, 4
    add esp, 4
    add esp, 4
    add esp, 4
    jmp $

        

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

;;--------------------------------------------------------------------------


;;
;; Rutina de atención del RELOJ
;; 

global _isr32
_isr32:

    pushad
    call fin_intr_pic1
    call sched_tarea_actual
    push eax
    call game_atender_tick            ; llamo a atender tick con el perro anterior
    call sched_atender_tick

    str cx
    cmp ax,cx
    je.fin

    jmp ax:0

    .fin:
    call screen_actualizar_reloj_global
    popad
    iret


;;------------------------------------------------------------------------- 

;;
;; Rutina de atención del TECLADO
;; 

global _isr33
_isr33:
    pushad
    call fin_intr_pic1
    in al, 0x60
    push eax
    call imprim
    add esp, 4
    popad
    iret

 


;;------------------------------------------------------------------------ 

;;
;; Rutinas de atención de las SYSCALLS
;;----------------------------------------------------------------------- ;;

global _isr70
_isr70:
    pushad

    ;str ebx
    mov ebx, game_perro_actual

    call fin_intr_pic1
    cmp eax, 0x1
    je moverse
    cmp eax, 0x2
    je cavar
    cmp eax, 0x3
    je olfatear
    jmp recibirOrden

    moverse:
        push ecx
        push ebx
        call game_perro_mover
        add esp, 4
        add esp, 4
        jmp fin

    cavar:
        push ebx
        call game_perro_cavar
        add esp, 4
        jmp fin

    olfatear:
        push ebx
        call game_perro_olfatear
        add esp, 4
        jmp fin

    recibirOrden:
        jmp fin

    fin:
        popad
        iret



