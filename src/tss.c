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
	// modificar aca la gdt 
	uint gdtAux = ((uint ) GDT_DESC.gdt_addr)+13*4;
	uint *puntGdt = (uint *) gdtAux;
	puntGdt += 2;
	*puntGdt = ((uint ) &tss_inicial) & 0x00FFFFFF;
	puntGdt += 12;
	*puntGdt = ((uint ) &tss_inicial) & 0x000000FF;
}

