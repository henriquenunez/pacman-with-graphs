//Implements graph discussed in header.

#include "graph.h"
#include "dstructures.h" //Simple data structures

#include <stdlib.h>

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
};

/*Helper macros*/

//#define __free_vertex(a_vertex) ((a_vertex.adj_list != NULL)  ? delete_list(a_vertex.adj_list); : ;)

/*Internal functions*/

void __initialize_vertex_matrix_graph(VERTEX*** matrix, int n_rows, int n_cols)
{
    VERTEX** init_matrix;

    //Vector to vectors
    init_matrix = (VERTEX**) malloc(n_rows * sizeof(VERTEX*));

    for (int i = 0 ; i < n_rows ; i++)
    {
	init_matrix[i] = (VERTEX*) calloc(n_cols, sizeof(VERTEX));
    }

    *matrix = init_matrix;
}

void __free_vertex_matrix_graph(VERTEX*** matrix, int n_rows, int n_cols)
{
    for (int i = 0 ; i < n_rows ; i++)
    {
	for (int j = 0 ; j < n_cols ; j++)
	{
		if( (*matrix)[i][j].adj_list != NULL)
		    delete_list((*matrix)[i][j].adj_list);
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

void insert_edge_graph(GRAPH* this_graph, PAIR source, PAIR destination)
{
    PAIR* this_adj_vertex; //Represents adjacence to a vertex

    //source: (row, col)

    //Error checking
    if (source.first >= this_graph->row_number &&
	source.second >= this_graph->col_number)
	return; //THIS IS AN ERROR. SHOULD BE HANDLED

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
/* TODO implement BFS
1  procedure BFS(G, start_v) is
2      let Q be a queue
3      label start_v as discovered
4      Q.enqueue(start_v)
5      while Q is not empty do
6          v := Q.dequeue()
7          if v is the goal then
8              return v
9          for all edges from v to w in G.adjacentEdges(v) do
10             if w is not labeled as discovered then
11                 label w as discovered
12                 w.parent := v
13                 Q.enqueue(w)
*/
    QUEUE* vertex_queue;

    vertex_queue = create_queue();
}

int value_at_vertex_graph(GRAPH* this_graph, PAIR source)
{
    //Error checking.
    if (source.first >= this_graph->row_number &&
	source.second >= this_graph->col_number)
	return -1; //THIS IS AN ERROR. SHOULD BE HANDLED

    return
	this_graph->vertex_matrix[source.first][source.second].value;
}

