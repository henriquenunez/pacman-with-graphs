#include "dstructures.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

    ret_list = (LIST*) calloc(1, sizeof(LIST));

    ret_list->internal_array = NULL;
    ret_list->size = 0;
    ret_list->iter_pos = 0;
    ret_list->capacity = 0;

    return ret_list;
}

void delete_list(LIST* this_list)
{
    //Free internal array
    free(this_list->internal_array);
    free(this_list);
}

void append_element_list(LIST* this_list, void* this_element)
{
    //In case we're out of space
    if(this_list->size+1 > this_list->capacity)
    {
	this_list->internal_array = realloc(this_list->internal_array,
				    (this_list->capacity + 10)* sizeof(void*));
	this_list->capacity+=10;
    }
    //printf("INTERNAL ARRAY%p\n", this_list->internal_array);
    //printf("SIZE%d\n", this_list->size);
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

void* remove_first_element_list(LIST* this_list)
{
    void* element;
    void** temp_internal_array;

    if (this_list->size <= 0) return NULL;

    element = this_list->internal_array[0];
    this_list->size--;

    //printf("Array pointer before: %p\n", this_list->internal_array);

    //Copies internal array from the next element until end.
    temp_internal_array = (void**) malloc(this_list->capacity * sizeof(void*));
    //printf("Temp pointer: %p\n", temp_internal_array);
    //printf("Internal array offset: %p\n", this_list->internal_array + 1);

    memcpy(temp_internal_array,
	    this_list->internal_array + 1, //Next value
	    this_list->size * sizeof(void*));
    //printf("Size copy: %d\n", this_list->size);

    free(this_list->internal_array);
    //Repoints internal array to right place.
    this_list->internal_array = temp_internal_array;

    //printf("Array pointer after: %p\n", this_list->internal_array);
    return element;
}

void reset_iter_list(LIST* this_list)
{
    this_list->iter_pos = 0;
}

void* iter_list(LIST* this_list)
{
    if (this_list == NULL || this_list->internal_array == NULL) return NULL;

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
    ret_queue->internal_list = create_list();

    return ret_queue;
}

void delete_queue(QUEUE* this_queue)
{
    delete_list(this_queue->internal_list);
    free(this_queue);
}

//Just wrappers for specific cases of lists
void en_queue(QUEUE* this_queue, void* this_element)
{
    append_element_list(this_queue->internal_list, this_element);
}

void* de_queue(QUEUE* this_queue)
{
    return remove_first_element_list(this_queue->internal_list);
}

