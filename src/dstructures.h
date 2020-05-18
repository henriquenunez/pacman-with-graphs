#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

/*Simple struct for holding pair of integers*/
typedef struct _pair {
    int first;
    int second;
} PAIR;

//List
typedef struct _list LIST;

LIST* create_list();
void delete_list(LIST*);

//Appends generic element
void append_element_list(LIST*, void*);
void* remove_last_element_list(LIST*);
void reset_iter_list();	//Resets iterator to beginning

//Returns elements, if reached end, iterator is reset and NULL is returned
void* iter_list();

//Queue
typedef struct _queue QUEUE;

QUEUE* create_queue();
void delete_queue(QUEUE*);

void en_queue(QUEUE*, void*);
void* de_queue(QUEUE*);

#endif

