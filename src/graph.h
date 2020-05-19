#ifndef GRAPH_H
#define GRAPH_H

#include "dstructures.h"

/*
This graph implementation uses a matrix representing ALL vertexes, and a list to
represent adjacences having the following form:
    0   1   2   3   4   5
0 |---|---|---|---|---|---|
1 |-A-|-B-|---|---|---|---|
2 |---|-C-|---|-D-|---|---|
3 |---|---|---|---|-E-|---|

In this example, the graph has 4X6(cartesian product) = 24 vertexes.

The following examples of pairs use the convention: (row, col)

For the sake of understandability, some lists have been attributed names to.
For example, the list A may contain:

[(1,2),(3,2),(3,5),(0,0)]

meaning that the vertex (1,0) is connected to

(1,2),
(3,2),
(3,5),
(0,0)

~Hiram
*/
typedef struct _graph GRAPH;
typedef struct _vertex VERTEX;

//Instantiation functions
GRAPH* create_graph(int n_rows, int n_cols);
void   delete_graph(GRAPH*);

void insert_edge_graph(GRAPH*, PAIR source, PAIR destination);

//BFS from origin to destination, fillig the distance on every iteration
void BFS_fill_distance_graph(GRAPH*, PAIR source, PAIR destination);
void BFS_reset_distance_graph(GRAPH*);

int value_at_vertex_graph(GRAPH*, PAIR source);

#endif

