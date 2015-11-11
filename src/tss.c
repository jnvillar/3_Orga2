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
	gdt[12].base_0_15 = (uint )&tss_inicial & 0x0000FFFF;
	gdt[12].base_23_16 = ((uint )&tss_inicial & 0x00FF0000) >> 4;
	gdt[12].base_31_24 = ((uint )&tss_inicial & 0xFF000000) >> 6;
	// idle
	gdt[13].base_0_15 = (uint )&tss_idle & 0x0000FFFF;
	gdt[13].base_23_16 = ((uint )&tss_idle & 0x00FF0000) >> 4;
	gdt[13].base_31_24 = ((uint )&tss_idle & 0xFF000000) >> 6;
	
	tss_idle.esp = 0x27000;
	tss_idle.ebp = 0x27000;
	tss_idle.cr3 = 0x27000;
	tss_idle.eip = 0x16000;	
	tss_idle.esp0 = 0x27000;
	tss_idle.ds = 0x48;
	tss_idle.ss = 0x48;
	tss_idle.es = 0x48;
	tss_idle.cs = 0x40;

	
}

void tss_completar(int jugador, int perro, perro_t *rrope){
	uint espCero = mmu_proxima_pagina_fisica_libre();
	if (jugador == 0 ){
		tss_jugadorA[perro].esp0 = espCero;
	    tss_jugadorA[perro].cs = 0x58;
	    tss_jugadorA[perro].es = 0x50;
	    tss_jugadorA[perro].gs = 0x50;
	    tss_jugadorA[perro].ss = 0x50;
	    tss_jugadorA[perro].ds = 0x50;
	    tss_jugadorA[perro].fs = 0x50;
	    tss_jugadorA[perro].eax = 0x0;
	    tss_jugadorA[perro].ebx = 0x0;
	    tss_jugadorA[perro].ecx = 0x0;
	    tss_jugadorA[perro].edx = 0x0;
	    tss_jugadorA[perro].esi = 0x0;
	    tss_jugadorA[perro].edi = 0x0;
	    tss_jugadorA[perro].esp = 0x0402000-12;
	    tss_jugadorA[perro].eip = 0x00401000;
	    tss_jugadorA[perro].eflags = 0x202;
		tss_jugadorA[perro].esp0 = espCero;
		tss_jugadorA[perro].eax = 0x0;
		tss_jugadorA[perro].iomap = 0xFFFF;
		tss_jugadorA[perro].ldt = 0x00000000;
		uint nuevoCr3 = mmu_inicializar_memoria_perro(rrope, jugador, perro);
		tss_jugadorA[perro].cr3 = nuevoCr3;


		gdt[15+perro].base_0_15 = (uint )&tss_jugadorA[perro] & 0x0000FFFF;
		gdt[15+perro].base_23_16 = ((uint )&tss_jugadorA[perro] & 0x00FF0000) >> 4;
		gdt[15+perro].base_31_24 = ((uint )&tss_jugadorA[perro] & 0xFF000000) >> 6;

	} else {
		tss_jugadorA[perro].esp0 = espCero;
	    tss_jugadorB[perro].cs = 0x84;
	    tss_jugadorB[perro].es = 0x72;
	    tss_jugadorB[perro].gs = 0x72;
	    tss_jugadorB[perro].ss = 0x72;
	    tss_jugadorB[perro].ds = 0x72;
	    tss_jugadorB[perro].fs = 0x72;
	    tss_jugadorB[perro].eax = 0x0;
	    tss_jugadorB[perro].ebx = 0x0;
	    tss_jugadorB[perro].ecx = 0x0;
	    tss_jugadorB[perro].edx = 0x0;
	    tss_jugadorB[perro].esi = 0x0;
	    tss_jugadorB[perro].edi = 0x0;
	    tss_jugadorB[perro].esp = 0x0402000-12;
	    tss_jugadorB[perro].eip = 0x00401000;
	    tss_jugadorB[perro].eflags = 0x202;
		tss_jugadorB[perro].esp0 = espCero;
		tss_jugadorB[perro].eax = 0x0;
		tss_jugadorB[perro].iomap = 0xFFFF;
		tss_jugadorB[perro].ldt = 0x00000000;
		uint nuevoCr3 = mmu_inicializar_memoria_perro(rrope, jugador, perro);
		tss_jugadorB[perro].cr3 = nuevoCr3;


		gdt[15+perro].base_0_15 = (uint )&tss_jugadorA[perro] & 0x0000FFFF;
		gdt[15+perro].base_23_16 = ((uint )&tss_jugadorA[perro] & 0x00FF0000) >> 4;
		gdt[15+perro].base_31_24 = ((uint )&tss_jugadorA[perro] & 0xFF000000) >> 6;
	}
}
