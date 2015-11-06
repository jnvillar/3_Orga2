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

void tss_completar(int jugador,p tss *miTss){
	uint *espCero = (uint *)mmu_proxima_pagina_fisica_libre();
	miTss.esp0 = espCero;
	

}