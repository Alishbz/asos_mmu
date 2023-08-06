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
 
 
Note: in 64 bit processors -> sizeof(uintptr_t) is 8 byte
      in 32 bit processors -> sizeof(uintptr_t) is 4 byte

**/
#include "asos_mmu.h"
   
 
#define ASOS_HEAP_SIZE     (sizeof(uintptr_t)*ASOS_HEAP_MAX_ALLOCATED_AREA_SIZE)

/** fake heap */
static unsigned char _HEAP[ASOS_HEAP_SIZE];

typedef struct {
    uintptr_t* adress;
    size_t size;
}pile_t;

typedef struct   {
    size_t count;
    pile_t spaces[ASOS_PILE_PROCESS_CAPACITY];
}pile_list_t;


static  pile_list_t   _freed_list;
static  pile_list_t   _allocated_list;



/** Interface for pile space memory management *************/
  

static void  _pile_list_insert( pile_list_t* const me,
                                const uintptr_t* adress,
                                size_t size)
{
    if (me == NULL || adress == NULL || !size) { 
        return; 
    }

    if (me->count + 1 >= ASOS_PILE_PROCESS_CAPACITY) {
        assert(" low ASOS_PILE_PROCESS_CAPACITY \n ");
        return;
    }

    me->spaces[me->count].adress = adress;
    me->spaces[me->count].size = size;

    size_t i = 0;

    for (i = me->count; i > 0; --i) {
        if ((me->count) &&
            (me->spaces[me->count].adress < me->spaces[me->count - 1].adress))
        {
            /** lower adress must be first allign  **/
            pile_t holder;
            holder.size = me->spaces[me->count].size;
            holder.adress = me->spaces[me->count].adress;
            me->spaces[me->count].adress = me->spaces[me->count - 1].adress;
            me->spaces[me->count].size = me->spaces[me->count - 1].size;
            me->spaces[me->count - 1].adress = holder.adress;
            me->spaces[me->count - 1].size = holder.size;
        }
    }
    me->count++;
}

static void  _pile_list_init(pile_list_t* const me)
{
    if ( me == NULL ) {
        return;
    }

    int  i = 0;

    me->count = 0;
    for (i = 0; i < ASOS_PILE_PROCESS_CAPACITY; i++) {
        me->spaces[0].adress = NULL;
        me->spaces[0].size = 0;
    }
}



static int _pile_list_index_find(const pile_list_t* me, uintptr_t* adress)
{
    if (me == NULL || adress == NULL || !me->count) {
        return -1;
    }

    size_t i = 0;

    for ( i = 0; i < me->count; ++i) {
        if (me->spaces[i].adress == adress) {
            return (int)i;
        }
    }

    return -1;
}

static void _pile_list_remove(pile_list_t* me, size_t index)
{
    if (me == NULL ) {
        return;
    }

    if (index > me->count-1 ) {
        assert(" index error \n ");
        return;
    }

    size_t i = 0;

    for ( i = index; i < me->count - 1; ++i) {
        me->spaces[i] = me->spaces[i + 1];
    }

    me->spaces[me->count - 1].adress = NULL;
    me->spaces[me->count - 1].size = 0;

    me->count -= 1;
}



/******** API ***************************************/


void* asos_malloc(size_t size_req)
{
    void* out = NULL;

    size_t size = size_req;

    if (!size_req) {
        return out;
    }

    if (size_req % sizeof(uintptr_t)) {
        size = ((size_req / sizeof(uintptr_t)) + 1 ) * sizeof(uintptr_t);   
    }
     
    if (size) {
     
        size_t i = 0;

        for (i = 0; i < _freed_list.count; i++) {

            const pile_t holder = _freed_list.spaces[i];

            if (size <= _freed_list.spaces[i].size) {
            
                _pile_list_remove(&_freed_list, i);

                const size_t update_free_size = holder.size - size;

                _pile_list_insert(&_allocated_list, holder.adress, size);

                if (update_free_size > 0) {

                    _pile_list_insert(&_freed_list, holder.adress + (size / sizeof(uintptr_t)), update_free_size);
                }

                out = (void*)holder.adress;

                break;
            }
        } 
    }
      
    return out;
}

  
void asos_free(void* me)
{
    if (me != NULL) {

        const int index = _pile_list_index_find(&_allocated_list, me);

        if (index >= 0) {

            _pile_list_insert(&_freed_list,
                              _allocated_list.spaces[index].adress,
                              _allocated_list.spaces[index].size);

#ifdef ASOS_HEAP_CONFIG_FOR_FREED_AREA_CLEAR
            memset(_allocated_list.spaces[index].adress, 0, _allocated_list.spaces[index].size);
#endif

            _pile_list_remove(&_allocated_list, (size_t)index);

        } 
    }
}

 

void asos_mmu_init(void)
{

    memset(_HEAP, 0, ASOS_HEAP_SIZE);

    _pile_list_init(&_allocated_list);

    _pile_list_init(&_freed_list);

    /** in the init all _HEAP are empty **/
    _pile_list_insert(&_freed_list, _HEAP , sizeof(_HEAP));
 
}


size_t asos_get_free_heap_size(void)
{
    size_t i = 0 , empty_area = 0;

    for (i = 0; i < _freed_list.count; i++) {
    
        empty_area += _freed_list.spaces[i].size;
    }

    return empty_area;
}


size_t asos_get_allocated_heap_size(void)
{
    size_t i = 0, allocate_area = 0;

    for (i = 0; i < _allocated_list.count; i++) {

        allocate_area += _allocated_list.spaces[i].size;
    }

    return allocate_area;
}








