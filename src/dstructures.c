#include "dstructures.h"

#include <stdlib.h>

/*Implementation of simple data structures*/

/*List*/

/*
/!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\
THIS LIST IMPLEMENTATION *REQUIRES* THE INTERNAL DATA TO BE FREED FROM THE
OUTSIDE.
MEMORY LEAKS *WILL* OCCUR OTHERWISE.
/!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\
*/

struct _list
{
    void** internal_array;
    size_t iter_pos;	    //Iterator position
    size_t capacity;
    size_t size;
};

LIST* create_list()
{
    LIST* ret_list;

    ret_list = (LIST*) malloc(sizeof(LIST));

    return ret_list;
}

void delete_list(LIST* this_list)
{
    free(this_list);
}

void append_element_list(LIST* this_list, void* this_element)
{
    //In case we're out of space
    if(this_list->size+1 > this_list->capacity)
    {
	this_list->internal_array = reallocarray(this_list->internal_array,
						    this_list->capacity + 10,
						    sizeof(void*));
	this_list->capacity+=10;
    }

    //Inserting in last position and updating size
    this_list->internal_array[this_list->size] = this_element;
    this_list->size++;
}

void* remove_last_element_list(LIST* this_list)
{
    void* element;

    if (this_list->size == 0) return NULL;

    this_list->size--;

    element = this_list->internal_array[this_list->size];
    this_list->internal_array[this_list->size] = NULL;

    return element;
}

void reset_iter_list(LIST* this_list)
{
    this_list->iter_pos = 0;
}

void* iter_list(LIST* this_list)
{
    if (this_list->iter_pos >= this_list->size)
    {
	reset_iter_list(this_list);
	return NULL;
    }

    return this_list->internal_array[this_list->iter_pos++];
}

/*Queue*/
struct _queue
{
    LIST* internal_list;
};

QUEUE* create_queue()
{
    QUEUE* ret_queue;

    ret_queue = (QUEUE*) malloc(sizeof(QUEUE));

    //Initialize list

    return ret_queue;
}

//Just wrappers for specific cases of lists
void en_queue(QUEUE* this_queue, void* this_element)
{
    append_element_list(this_queue->internal_list, this_element);
}

void* de_queue(QUEUE* this_queue)
{
    return remove_last_element_list(this_queue->internal_list);
}

