/* ** por compatibilidad se omiten tildes **
================================================================================
TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
definicion de funciones del scheduler
*/

#include "sched.h"
#include "i386.h"
#include "screen.h"

sched_t scheduler;

void sched_inicializar()
{
	scheduler.current = 0;
	int i = 0;

	while(i<MAX_CANT_TAREAS_VIVAS){		
		scheduler.tasks[i].gdt_index = 14; //	Tarea iddle
		scheduler.tasks[i].perro_t = NULL; 
		i++;		
	}
}


int sched_buscar_indice_tarea(uint gdt_index) {
    int i = 0;
    while(i<MAX_CANT_TAREAS_VIVAS){
    	if(scheduler.tasks[i].perro_t != NULL && scheduler.tasks[i].gdt_index == gdt_index){
    		return i;
    	}
    	i++;
    }
    return -1;    
}


int sched_buscar_tarea_libre()
{
	int i = 0;
	while(i<MAX_CANT_TAREAS_VIVAS){
		if(scheduler.tasks[i].perro_t == NULL){
			return i;			
		}
		i++;
	}
	return -1;
}



perro_t* sched_tarea_actual()
{
    return scheduler.tasks[scheduler.current].perro;
}

void sched_agregar_tarea(perro_t *perro)
{
	int i = sched_buscar_tarea_libre()
	if(i != -1){
		scheduler.tasks[i].perro_t = perro;
		scheduler.tasks[i].gdt_index = i + 15;
		agergar a la gdt 8 perros;
	}
}

void sched_remover_tarea(unsigned int gdt_index)
{
	int i = 0;
	while(i<MAX_CANT_TAREAS_VIVAS){
		if(scheduler.tasks[i].gdt_index = gdt_index){
			scheduler.tasks[i].perro_t = NULL;
		}
	}

	Limpiar pantalla
}


uint sched_proxima_a_ejecutar()
{
	int i = scheduler.current;
	int j = 0;
	while(j<MAX_CANT_TAREAS_VIVAS){
		if(scheduler.tasks[i%MAX_CANT_TAREAS_VIVAS].perro_t != NULL){
			return i%MAX_CANT_TAREAS_VIVAS;
		}
		j++;
		i++;
	}    
}


ushort sched_atender_tick()
{
   
    if(sched_tarea_actual() == sched_proxima_a_ejecutar().perro_t){    	
    	return scheduler.tasks[scheduler.current].gdt_index;
    }else{
    	scheduler.current = sched_proxima_a_ejecutar();
    	return scheduler.tasks[scheduler.current].gdt_index;
    }
    
}


