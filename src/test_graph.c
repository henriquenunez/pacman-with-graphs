#include <stdio.h>

#include "graph.h"

#define ROWS 5
#define COLS 9

int main()
{
    GRAPH* a_graph;
    PAIR temp_pair_0;
    PAIR temp_pair_1;


    //Source (0,0)
    temp_pair_0.first = 0;
    temp_pair_0.second = 0;
    //Destination (1,1)
    temp_pair_1.first = 1;
    temp_pair_1.second = 1;

    a_graph = create_graph(ROWS, COLS);
    insert_edge_graph(a_graph, temp_pair_0, temp_pair_1);
    delete_graph(a_graph);


    return 0;
}
