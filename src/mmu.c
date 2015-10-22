/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"
#include "i386.h"
/* Atributos paginas */
/* -------------------------------------------------------------------------- */




/* Direcciones fisicas de codigos */
/* -------------------------------------------------------------------------- */
/* En estas direcciones estan los códigos de todas las tareas. De aqui se
 * copiaran al destino indicado por TASK_<i>_CODE_ADDR.
 */

/* Direcciones fisicas de directorios y tablas de paginas del KERNEL */
/* -------------------------------------------------------------------------- */

void mmu_mapear_pagina(uint virtual, uint cr3, uint fisica, uint attrs){
	uint pagDir = ((cr3 >> 12) + (virtual >> 22))*4;
	if ( &pagDir % 2 == 1){
		uint basePag = &pagDir >> 12;
		uint pageDirAux = &pageDir 
		pageDirAux = pageDirAux & 0;
		if (pageDirAux % 4 == 0 && attrs[1] == 1){ 			// si r/w == 0 y attrs es de r/w
			&pagDir = &pagDir | 10;
		}
		pageDirAux = pageDirAux & 00;
		if (pageDirAux % 8 != 0 && attrs[2] == 0){ 			// si u/s == 1 y attrs es de supervisor
			&pagDir = &pagDir & 011;
		}
	} else {
		uint basePag = mmu_proxima_pagina_fisica_libre();
		limpiar (menos el que nosotros queremos crear)
	}
	uint pageTable = &basePag + ((virtual & 0x003fffff) >> 12);
	&pageTable = &pageTable & ~&pageTable;
	&pageTable = &pageTable | attrs;
	&pageTable = &pageTable | (fisica << 12);

}