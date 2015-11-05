; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "imprimir.mac"

global start
extern GDT_DESC
extern IDT_DESC
extern aux_limpiarPantalla
extern screen_inicializar
extern idt_inicializar
extern game_inicializar
extern mmu_inicializar_dir_kernel
extern imprimirNombre
extern mmu_unmapear_pagina
extern mmu_inicializar_memoria_perro
extern deshabilitar_pic
extern resetear_pic
extern habilitar_pic



;; Saltear seccion de datos
jmp start

;;
;; Seccion de datos.
;; -------------------------------------------------------------------------- ;;
iniciando_mr_msg db     'Iniciando kernel (Modo Real)...'
iniciando_mr_len equ    $ - iniciando_mr_msg

iniciando_mp_msg db     'Iniciando kernel (Modo Protegido)...'
iniciando_mp_len equ    $ - iniciando_mp_msg

;;
;; Seccion de código.
;; -------------------------------------------------------------------------- ;;

;; Punto de entrada del kernel.
BITS 16
start:
    ; Deshabilitar interrupciones
    cli

    ; Cambiar modo de video a 80 X 50
    mov ax, 0003h
    int 10h ; set mode 03h
    xor bx, bx
    mov ax, 1112h
    int 10h ; load 8x8 font

    ; Imprimir mensaje de bienvenida
    imprimir_texto_mr iniciando_mr_msg, iniciando_mr_len, 0x07, 0, 0


    ; Habilitar A20

    call habilitar_A20

    imprimir_texto_mr iniciando_mr_msg, iniciando_mr_len, 0x07, 0, 0

    ; Cargar la GDT

    lgdt [GDT_DESC] 

    ; Setear el bit PE del registro CR0

    mov eax, cr0
    or eax, 1
    mov cr0, eax

    ; Saltar a modo protegido

    jmp 0x40:modoprotegido


    modoprotegido:
BITS 32

    ; Establecer selectores de segmentos

    mov ax, 0x48
    mov ds, ax
    mov ax, 0x48
    mov ss, ax

    ; Establecer la base de la pila

    mov ebp, 0x27000
    mov esp, 0x27000

    ; Imprimir mensaje de bienvenida


    mov ax, 0x60
    mov fs, ax
    mov word [fs:0x00], 0x1023
    mov word [fs:0x02], 0x1024
    mov word [fs:0x04], 0x1024
    mov word [fs:0x06], 0x1024


    ; Inicializar el juego

    call game_inicializar

    ; Inicializar pantalla

    call aux_limpiarPantalla    
    call screen_inicializar

    ; Inicializar el manejador de memoria



    ; Inicializar el directorio de paginas

    call mmu_inicializar_dir_kernel


    ; Cargar directorio de paginas

    mov eax, 0x00027000
    mov cr3, eax

    ; Habilitar paginacion
    

    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax

     

    ;call mmu_inicializar_memoria_perro


    ;xchg bx, bx
    call imprimirNombre

    ; Inicializar tss

    ; Inicializar tss de la tarea Idle

    ; Inicializar el scheduler

    ; Inicializar la IDT

    call idt_inicializar

    ; Cargar IDT

    lidt [IDT_DESC]

    ;mov eax, 0
    ;mov ecx, 1
    ;div ecx

    ; Configurar controlador de interrupciones

    ; Cargar tarea inicial

    ; Habilitar interrupciones
  
  
   
   call deshabilitar_pic
   call resetear_pic
   call habilitar_pic
   sti

    ; Saltar a la primera tarea: Idle

    xchg bx, bx
    ; Ciclar infinitamente (por si algo sale mal...)

    mov eax, 0xFFFF
    mov ebx, 0xFFFF
    mov ecx, 0xFFFF
    mov edx, 0xFFFF
    
    

    jmp $
    jmp $

;; -------------------------------------------------------------------------- ;;

%include "a20.asm"
