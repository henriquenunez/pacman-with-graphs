//Implements graph discussed in header.

#include "graph.h"
#include "dstructures.h" //Simple data structures

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

struct _graph
{
    VERTEX** vertex_matrix;
    int row_number;
    int col_number;
};

struct _vertex
{
    LIST* adj_list;  //List holding pairs, representig adj. vertexes.
    int value;	    //Value
    bool visited;
};

/*Helper macros*/

//#define __free_vertex(a_vertex) ((a_vertex.adj_list != NULL)  ? delete_list(a_vertex.adj_list); : ;)

/*Internal functions*/

void __initialize_vertex_matrix_graph(VERTEX*** matrix, int n_rows, int n_cols)
{
    VERTEX** init_matrix;

    //Vector to vectors
    init_matrix = (VERTEX**) malloc(n_rows * sizeof(VERTEX*));

    //Will zero the entire row.
    for (int i = 0 ; i < n_rows ; i++)
    {
	init_matrix[i] = (VERTEX*) calloc(n_cols, sizeof(VERTEX));
    }

    *matrix = init_matrix;
}

void __free_vertex_matrix_graph(VERTEX*** matrix, int n_rows, int n_cols)
{
    void* temp_pointer;

    for (int i = 0 ; i < n_rows ; i++)
    {
	for (int j = 0 ; j < n_cols ; j++)
	{
		if( (*matrix)[i][j].adj_list != NULL) //Delete list.
		{
		    while((temp_pointer =
			    remove_last_element_list((*matrix)[i][j].adj_list))
									!= NULL)
			free(temp_pointer);
		    delete_list((*matrix)[i][j].adj_list);
		}
	}
	free((*matrix)[i]);
    }

    free(*matrix);

    *matrix = NULL;
}

/*Exposed functions*/

GRAPH* create_graph(int n_rows, int n_cols)
{
    GRAPH* ret_graph;

    ret_graph = (GRAPH*) malloc(sizeof(GRAPH));
    ret_graph->row_number = n_rows;
    ret_graph->col_number = n_cols;

    /*Initialize vertexes matrix*/
    __initialize_vertex_matrix_graph(&ret_graph->vertex_matrix,
					n_rows,
					n_cols);

    return ret_graph;
}

void delete_graph(GRAPH* this_graph)
{
    __free_vertex_matrix_graph(&this_graph->vertex_matrix,
				this_graph->row_number,
				this_graph->col_number);

    free(this_graph);
}

#define V_MAT (this_graph->vertex_matrix) //Helper macro

void insert_edge_graph(GRAPH* this_graph, PAIR source, PAIR destination)
{
    PAIR* this_adj_vertex; //Represents adjacence to a vertex.

    //source: (row, col)

    //Error checking
    if (source.first >= this_graph->row_number &&
	source.second >= this_graph->col_number)
	return; //THIS IS AN ERROR. SHOULD BE HANDLED

    //Error checking
    if (destination.first >= this_graph->row_number &&
	destination.second >= this_graph->col_number)
	return; //THIS IS AN ERROR. SHOULD BE HANDLED

    //Checks whether list exists or not.
    //TODO THIS CHECK IS NOT BEING MADE
    //printf("ADJ_LIST: %p\n", V_MAT[source.first][source.second].adj_list);
    if (V_MAT[source.first][source.second].adj_list == NULL)
		V_MAT[source.first][source.second].adj_list = create_list();

    //Copies destination vertex to heap, so list is able to store.
    this_adj_vertex = (PAIR*) malloc(sizeof(PAIR));
    this_adj_vertex->first = destination.first;
    this_adj_vertex->second = destination.second;

    //Inserts destination pair into correspondent vertex's adj. list.
    append_element_list(
	this_graph->vertex_matrix[source.first][source.second].adj_list,
	this_adj_vertex);
}


void BFS_fill_distance_graph(GRAPH* this_graph, PAIR source, PAIR destination)
{
    //Pointer to temp. ordered pair representing vertex row and col.
    PAIR* current_vertex_pair;

    //Pointer to temp child reference of ordered pair.
    PAIR* temp_child_vertex_pair;

    unsigned int dist_counter;
    QUEUE* vertex_queue;    //Creates queue
    PAIR* pair_pointer;	    //Pointer to pair that MUST BE INITIALIZED ONCE.

    vertex_queue = create_queue();

    dist_counter = 0;  //Distance counter

    V_MAT[source.first][source.second].visited = true; //Mark as visited
    pair_pointer = current_vertex_pair = create_pair;
    current_vertex_pair->first = source.first;
    current_vertex_pair->second = source.second;
    en_queue(vertex_queue, current_vertex_pair); //Enqueue initial vtx.

    //Attribute and check if queue was empty.
    while ((current_vertex_pair = (PAIR*) de_queue(vertex_queue)) != NULL)
    {
	if (current_vertex_pair->first == destination.first &&
	    current_vertex_pair->second == destination.second)
	{
	    break;
	}
	dist_counter++;
	printf("Current distance: %u\n", dist_counter);
	while ((temp_child_vertex_pair = (PAIR*) iter_list(
			    V_MAT[current_vertex_pair->first]
				    [current_vertex_pair->second].adj_list
								    )) != NULL)
	{
	    //In case vertex already visited.
	    if (V_MAT[temp_child_vertex_pair->first]
			    [temp_child_vertex_pair->second].visited) continue;

	    printf("C: (%d,%d)\n", temp_child_vertex_pair->first,
					    temp_child_vertex_pair->second);


	    //Mark vertex as visited.
	    V_MAT[temp_child_vertex_pair->first]
			    [temp_child_vertex_pair->second].visited = true;

	    //Insert distance into vertex.
	    V_MAT[temp_child_vertex_pair->first]
			    [temp_child_vertex_pair->second].value =
								dist_counter;

	    en_queue(vertex_queue, temp_child_vertex_pair);
	}
	/*printf("List of vertex (%d,%d) over.\n", current_vertex_pair->first,
						 current_vertex_pair->second);*/
    }

    /* Here, there's no need to free the vertexes in queue, since they are being
     * referenced from another list. Delete graph function already handles this.
     */

    //Deleting that const pair, used in the beginning of the list
    delete_pair(pair_pointer);
    delete_queue(vertex_queue);

}

void BFS_reset_visits_graph(GRAPH* this_graph)
{
    //ATTENTION: NOT READY
    for (int i = 0 ; i < this_graph->row_number ; i++)
	for (int j = 0 ; j < this_graph->col_number ; j++)
	{
	    V_MAT[i][j].visited = false;
	}
}


int value_at_vertex_graph(GRAPH* this_graph, PAIR source)
{
    //Error checking.
    if (source.first >= this_graph->row_number &&
	source.second >= this_graph->col_number)
	return -1; //THIS IS AN ERROR. SHOULD BE HANDLED

    return
	V_MAT[source.first][source.second].value;
}

#undef V_MAT

