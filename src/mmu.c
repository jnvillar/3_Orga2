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

extern void aux_limpiarPantalla();
extern void print(const char * text, unsigned int x, unsigned int y, unsigned short attr);
uint pagLibre = 0x100000;
uint cantPagLibre = 768;

/* Direcciones fisicas de codigos */
/* -------------------------------------------------------------------------- */
/* En estas direcciones estan los códigos de todas las tareas. De aqui se
 * copiaran al destino indicado por TASK_<i>_CODE_ADDR.
 */

/* Direcciones fisicas de directorios y tablas de paginas del KERNEL */
/* -------------------------------------------------------------------------- */


void mmu_mapear_pagina(uint virtual, uint cr3, uint fisica, uint attrs){
	uint *pagDir = (uint *) ((cr3 & 0xFFFFF000) + ((virtual >> 22 )*4));

	uint *pageTable;
	uint *pageTableEntry;
	if ( *pagDir % 2 == 1){ 				// ESTA PRESENTE?
		
		
		pageTableEntry = (uint *) ((*pagDir & 0xFFFFF000) + ((virtual >> 12) & 0x000003FF)*4);
		uint pageDirAux = *pagDir;
		pageDirAux = pageDirAux & 0xFFFFFFFE;
		uint atr_aux = attrs;
		atr_aux = atr_aux >> 1;
		if (pageDirAux % 4 == 0 && atr_aux % 2 == 1){ 			// si r/w == 0 y attrs es de r/w
			*pagDir = *pagDir | 10;

		}
		atr_aux = atr_aux >> 1;		
		pageDirAux = pageDirAux & 0xFFFFFFFC;
		if (pageDirAux % 8 != 0 && atr_aux % 2 == 0){ 			// si u/s == 1 y attrs es de supervisor
			*pagDir = *pagDir & 0xFFFFFFFB;
		}
	} else {
		pageTable = (uint *) mmu_proxima_pagina_fisica_libre();
		*pagDir = ((uint )pageTable & 0xFFFFF000) | 0x00000007;			// LE PASAMOS LA DIRECCION DE LA TABLA Y EL PRESENTE
		
		pageTableEntry = pageTable + ((virtual >> 12) & 0x000003FF)*4;
		mmu_inicializar_pagina(pageTable);
	}
	


	*pageTableEntry = 0x00000000 | fisica;
	*pageTableEntry = (*pageTableEntry & 0xFFFFF000) | attrs;

}



uint mmu_inicializar_dir_kernel(){
	
	mmu_inicializar_pagina((uint *)0x00027000);
	uint cr3 = 0x00027000;
	uint attrs = 0x007;
	int i = 0x00000000;
	while (i<1024){
		mmu_mapear_pagina(i*4096,cr3,i*4096,attrs);
		i++;
	}
	return cr3; 

}


uint mmu_proxima_pagina_fisica_libre(){
	pagLibre += 4096;
	cantPagLibre--;
	return pagLibre-4096;
}


void mmu_inicializar_pagina(uint * pagina){
	int i = 0;
	while(i<4096){
		*pagina = 0x00000000;
		pagina += 32;
		i++;
	}
}

uint mmu_unmapear_pagina(uint virtual, uint cr3){
	uint *pagDir = (uint *) ((cr3 & 0xFFFFF000) + ((virtual >> 22 )*4));

	uint *pageTableEntry;
	if ( *pagDir % 2 == 1){ 				// ESTA PRESENTE?
		pageTableEntry = (uint *) ((*pagDir & 0xFFFFF000) + ((virtual >> 12) & 0x000003FF)*4);
	} else {
		return 0;
	}
	*pageTableEntry = 0x00000000;
	return 0;
}



void mmu_inicializar(){

}

/*
uint mmu_inicializar_memoria_perro(perro_t *perro, int index_jugador, int index_tipo){
	uint *pagDir = mmu_proxima_pagina_fisica_libre();
	mmu_inicializar_pagina(pagDir);
	
}
*/