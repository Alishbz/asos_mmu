/****************************************************************************************
* ALI SAHBAZ
*
* ASOS Framework - "Ali Sahbaz Operating System"
* 
* MMU - "Memory Management Unit" 
*
* Description: it is a GPOS memory controller , 
*
* Date          : 05.08.2023
* By            : Ali Sahbaz
* e-mail        : ali_sahbaz@outlook.com
*/
#pragma once
#ifndef ASOS_MMU_H
#define ASOS_MMU_H

#ifdef __cplusplus
extern "C"
{
#endif
	 

#include <stdio.h>   
#include <stdlib.h> 
#include <assert.h> 
#include <string.h> 

/** user config -> ASOS_HEAP_FREE_MANAGER_CAPACITY , it is capacity of empty memory areas manager , freed areas spaces holder max size */
#define ASOS_PILE_PROCESS_CAPACITY                500   

/** user config -> ASOS_HEAP_MAX_ALLOCATED_AREA_SIZE */
#define ASOS_HEAP_MAX_ALLOCATED_AREA_SIZE         1000

/** user config -> ASOS_HEAP_CONFIG_FOR_FREED_AREA_CLEAR if it is active then freed area default cleared '0'   */
#define ASOS_HEAP_CONFIG_FOR_FREED_AREA_CLEAR         1  // OR comment






void asos_mmu_init(void);

void* asos_malloc(size_t size_req);

void asos_free(void* me);

size_t asos_get_free_heap_size(void);

size_t asos_get_allocated_heap_size(void);



#ifdef __cplusplus
}
#endif

#endif