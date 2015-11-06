/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "tss.h"
#include "mmu.h"



tss tss_inicial;
tss tss_idle;

tss tss_jugadorA[MAX_CANT_PERROS_VIVOS];
tss tss_jugadorB[MAX_CANT_PERROS_VIVOS];

void tss_inicializar() {
	
	// modificamos aca la gdt 
	// tarea inicial
	gdt[13].base_0_15 = (uint )&tss_inicial & 0x0000FFFF;
	gdt[13].base_23_16 = ((uint )&tss_inicial & 0x00FF0000) >> 4;
	gdt[13].base_31_24 = ((uint )&tss_inicial & 0xFF000000) >> 6;
	// idle
	gdt[14].base_0_15 = (uint )&tss_idle & 0x0000FFFF;
	gdt[14].base_23_16 = ((uint )&tss_idle & 0x00FF0000) >> 4;
	gdt[14].base_31_24 = ((uint )&tss_idle & 0xFF000000) >> 6;
	
	tss_idle.esp = 0x27000;
	tss_idle.ebp = 0x27000;
	tss_idle.cr3 = 0x27000;
	tss_idle.eip = 0x16000;	
	tss_idle.esp0 = 0x27000;
	tss_idle.ds = 0x48;
	tss_idle.ss = 0x48;

	
}

void tss_completar(int jugador, int perro, perro_t *rrope){
	uint *espCero = (uint *)mmu_proxima_pagina_fisica_libre();
	if (jugador == 0 ){
	tss_jugadorA[perro].esp0 = espCero;
    tss_jugadorA[perro].unused0 = 0x00000000;
    tss_jugadorA[perro].ss0 =?;
    tss_jugadorA[perro].unused = 0x00000000;
    tss_jugadorA[perro].esp1 = esp1;
    tss_jugadorA[perro].cs = 0x0003;
    tss_jugadorA[perro].es = 0x0003;
    tss_jugadorA[perro].gs = 0x0003;
    tss_jugadorA[perro].ss = 0x0003;
    tss_jugadorA[perro].ds = 0x0003;
    tss_jugadorA[perro].fs = 0x0003;
    tss_jugadorA[perro].eax = 0x0;
    tss_jugadorA[perro].ebx = 0x0;
    tss_jugadorA[perro].ecx = 0x0;
    tss_jugadorA[perro].edx = 0x0;
    tss_jugadorA[perro].esi = 0x0;
    tss_jugadorA[perro].edi = 0x0;
    tss_jugadorA[perro].esp = 0x0402000-12;
    tss_jugadorA[perro].eip = 0x00401000;
    tss_jugadorA[perro].eeflags = 0x202;
	tss_jugadorA[perro].eax = espCero;
	tss_jugadorA[perro].eax = 0x0;
	tss_jugadorA[perro].iomap = 0xFFFF0000;
	tss_jugadorA[perro].ldt = 0x00000000;
	uint *nuevoCr3 = mmu_inicializar_memoria_perro(rrope, jugador, perro);
	tss_jugadorA[perro].cr3 = nuevoCr3;


	}


}