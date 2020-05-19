#include <stdio.h>
#include <stdlib.h>

#include "dstructures.h"

int main()
{
    LIST* a_list;
    QUEUE* a_queue;
    PAIR* a_pair;

    a_list = create_list();

    //Inserting elements into list
    for (int i = 0 ; i < 10 ; i++)
    {
	a_pair = create_pair;
	a_pair->first = i;
	a_pair->second = i;

	append_element_list(a_list, a_pair);
    }

    printf("List test:\n");
    while ((a_pair = iter_list(a_list)) != NULL)
    {
	printf("First: %d & Second: %d\n", a_pair->first, a_pair->second);
	delete_pair(a_pair);
    }

    delete_list(a_list);
    a_list = create_list();

    //Inserting elements into list
    for (int i = 0 ; i < 10 ; i++)
    {
	a_pair = create_pair;
	a_pair->first = i;
	a_pair->second = i;

	append_element_list(a_list, a_pair);
    }

    printf("List test:\n");
    //Removing from beginning, result should be the same as queue
    for (int i = 0 ; i < 10 ; i++)
    {
	a_pair = remove_first_element_list(a_list);
	printf("First: %d & Second: %d\n", a_pair->first, a_pair->second);
	delete_pair(a_pair);
    }


    delete_list(a_list);

    a_queue = create_queue();
    printf("Queue test:\n");

    //Inserting elements into queue
    for (int i = 0 ; i < 3 ; i++)
    {
	a_pair = create_pair;
	a_pair->first = i;
	a_pair->second = i;

	en_queue(a_queue, a_pair);
    }

    for (int i = 20 ; i < 30 ; i++)
    {
	a_pair = create_pair;
	a_pair->first = i;
	a_pair->second = i;

	en_queue(a_queue, a_pair);
    }

    for(int i = 3 ; i < 10 ; i++)
    {
    	a_pair = create_pair;
	a_pair->first = i;
	a_pair->second = i;

	en_queue(a_queue, a_pair);
    }

    while((a_pair = de_queue(a_queue)) != NULL)
    {
	printf("First: %d & Second: %d\n", a_pair->first, a_pair->second);
	delete_pair(a_pair);
    }

    delete_queue(a_queue);

    return 0;
}
