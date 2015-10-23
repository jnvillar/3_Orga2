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


uint pagLibre = 0x100000;

/* Direcciones fisicas de codigos */
/* -------------------------------------------------------------------------- */
/* En estas direcciones estan los códigos de todas las tareas. De aqui se
 * copiaran al destino indicado por TASK_<i>_CODE_ADDR.
 */

/* Direcciones fisicas de directorios y tablas de paginas del KERNEL */
/* -------------------------------------------------------------------------- */

void mmu_mapear_pagina(uint virtual, uint cr3, uint fisica, uint attrs){
	
	uint *pagDir = (uint *) (cr3 & 0xFFFFF000 + ((virtual & 0xFFC00000)*4));
	//uint *pagDir = (uint *) (((cr3 >> 12) + (virtual >> 22))*4);
	uint *basePag;
	if ( *pagDir % 2 == 1){
		//basePag = (uint *) (*pagDir >> 12);
		basePag = (uint *) (*pagDir & 0xFFFFF000);
		uint pageDirAux = *pagDir;
		pageDirAux = pageDirAux & 0;
		uint atr_aux = attrs;
		atr_aux = atr_aux >> 1;
		if (pageDirAux % 4 == 0 && atr_aux % 2 == 1){ 			// si r/w == 0 y attrs es de r/w
			*pagDir = *pagDir | 10;
		}
		atr_aux = atr_aux >> 1;		
		pageDirAux = pageDirAux & 00;
		if (pageDirAux % 8 != 0 && atr_aux % 2 == 0){ 			// si u/s == 1 y attrs es de supervisor
			*pagDir = *pagDir & 011;
		}
	} else {
		basePag = (uint *) mmu_proxima_pagina_fisica_libre();
		//limpiar (menos el que nosotros queremos crear);
	}
	uint *pageTable = basePag + ((virtual & 0x003fffff) & 0xFFFFF000);
	*pageTable = *pageTable & ~*pageTable;
	*pageTable = *pageTable | attrs;
	*pageTable = *pageTable | (fisica << 12);

}


void mmu_inicializar(){
	uint cr3 = 0x27000000;
	uint attrs = 0x003;
	int i = 0;
	while (i<4194304){
		mmu_mapear_pagina(i,cr3,i,attrs);
		i+=4096;	
	}	
}


uint mmu_proxima_pagina_fisica_libre(){
	pagLibre += 4096;
	return pagLibre-4096;
}
