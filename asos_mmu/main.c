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

#include <stdio.h>

#include "asos_mmu.h"
 
int main() {

    asos_mmu_init();
      
    printf("ASOS MMU : test starting ... \n\n"); 

    printf("ASOS MMU : allocation starting ... \n\n");

    char* test1 = (char *)asos_malloc(126);
     
    printf("ASOS MMU : remaining memory %d  \n", (int)asos_get_free_heap_size() );
    printf("ASOS MMU : allocated memory %d  \n", (int)asos_get_allocated_heap_size());
    printf("\n\n");

    char* test2 = (char*)asos_malloc(35);

    printf("ASOS MMU : remaining memory %d  \n", (int)asos_get_free_heap_size());
    printf("ASOS MMU : allocated memory %d  \n", (int)asos_get_allocated_heap_size());
    printf("\n\n");


    char* test3 = (char*)asos_malloc(254);

    printf("ASOS MMU : remaining memory %d  \n", (int)asos_get_free_heap_size());
    printf("ASOS MMU : allocated memory %d  \n", (int)asos_get_allocated_heap_size());
    printf("\n\n");


    test1[0] = 15;
    test1[1] = 16;
    test1[2] = 17;

    test2[0] = 25;
    test2[1] = 26;
    test2[2] = 27;
     
    test3[0] = 35;
    test3[1] = 36;
    test3[2] = 37;
     
    printf("ASOS MMU : free starting ... \n\n");
  
    asos_free((void*)test2);

    printf("ASOS MMU : remaining memory %d  \n", (int)asos_get_free_heap_size());
    printf("ASOS MMU : allocated memory %d  \n", (int)asos_get_allocated_heap_size());
    printf("\n\n");

     

    printf("ASOS MMU : allocation starting ... \n\n");

    char* test4 = (char*)asos_malloc(16);

    printf("ASOS MMU : remaining memory %d  \n", (int)asos_get_free_heap_size());
    printf("ASOS MMU : allocated memory %d  \n", (int)asos_get_allocated_heap_size());
    printf("\n\n");
     
    test4[0] = 45;
    test4[1] = 46;
    test4[2] = 47;


    char* test5 = (char*)asos_malloc(7);

    printf("ASOS MMU : remaining memory %d  \n", (int)asos_get_free_heap_size());
    printf("ASOS MMU : allocated memory %d  \n", (int)asos_get_allocated_heap_size());
    printf("\n\n");

    test5[0] = 55;
    test5[1] = 56;
    test5[2] = 57;

    return 0;
}