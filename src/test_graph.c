#include <stdio.h>

#include "graph.h"

const int ROWS = 5;
const int COLS = 9;

#define mod(a, b) ((a%b < 0) ? ((a%b) + b) : (a%b))

int main()
{
    GRAPH* a_graph;
    PAIR source, destination;

    a_graph = create_graph(ROWS, COLS);

    printf("30 MOD 30: %d\n", mod(30, 30));

    //Testing Initial graph
    printf("Init graph:\n");
    for (int i = 0 ; i < ROWS ; i++)
    {
	for (int j = 0 ; j < COLS ; j++)
	{
	    source.first = i; source.second = j;
	    printf("%d ", value_at_vertex_graph(a_graph, source));
	}
	printf("\n");
    }

    printf("Creating edges\n");
    for (int i = 0 ; i < ROWS ; i++)
    {
	for (int j = 0 ; j < COLS ; j++)
	{
	    source.first = i; source.second = j;

	    //Up
	    destination.first = (i - 1);
	    destination.second = (j);
	    destination.first = mod(destination.first, ROWS);
	    destination.second = mod(destination.second, COLS);
	    insert_edge_graph(a_graph, source, destination);

	    //Left
	    destination.first = (i) % ROWS;
	    destination.second = (j - 1) % COLS;
	    destination.first = mod(destination.first, ROWS);
	    destination.second = mod(destination.second, COLS);
	    insert_edge_graph(a_graph, source, destination);

	    //Down
	    destination.first = (i + 1) % ROWS;
	    destination.second = (j) % COLS;
	    destination.first = mod(destination.first, ROWS);
	    destination.second = mod(destination.second, COLS);

	    insert_edge_graph(a_graph, source, destination);

	    //Right
	    destination.first = (i) % ROWS;
	    destination.second = (j + 1) % COLS;
	    destination.first = mod(destination.first, ROWS);
	    destination.second = mod(destination.second, COLS);

	    insert_edge_graph(a_graph, source, destination);
	}
    }

    source.first = 0; source.second = 0;
    destination.first = (int) ROWS / 2; destination.second = (int) COLS / 2;
    printf("Source:	    (%d,%d)\n", source.first, source.second);
    printf("Destination:    (%d,%d)\n", destination.first, destination.second);

    //Testing BFS
    BFS_fill_distance_graph(a_graph, source, destination);

    printf("After BFS:\n");

    printf("    ");
    for (int j = 0 ; j < COLS ; j++)
	printf("%3d ", j);
    printf("\n");

    for (int i = 0 ; i < ROWS ; i++)
    {
	printf("%3d:", i);
	for (int j = 0 ; j < COLS ; j++)
	{
	    source.first = i; source.second = j;
	    printf("%3d ", value_at_vertex_graph(a_graph, source));
	}
	printf("\n");
    }

    //Cleaning BFS
    BFS_reset_distance_graph(a_graph);
    printf("After BFS clean:\n");

    printf("    ");
    for (int j = 0 ; j < COLS ; j++)
	printf("%3d ", j);
    printf("\n");

    for (int i = 0 ; i < ROWS ; i++)
    {
	printf("%3d:", i);
	for (int j = 0 ; j < COLS ; j++)
	{
	    source.first = i; source.second = j;
	    printf("%3d ", value_at_vertex_graph(a_graph, source));
	}
	printf("\n");
    }

    source.first = 2; source.second = 2;
    destination.first = 3; destination.second = 6;
    printf("Source:	    (%d,%d)\n", source.first, source.second);
    printf("Destination:    (%d,%d)\n", destination.first, destination.second);

    //Testing BFS
    BFS_fill_distance_graph(a_graph, source, destination);

    printf("After BFS:\n");

    printf("    ");
    for (int j = 0 ; j < COLS ; j++)
	printf("%3d ", j);
    printf("\n");

    for (int i = 0 ; i < ROWS ; i++)
    {
	printf("%3d:", i);
	for (int j = 0 ; j < COLS ; j++)
	{
	    source.first = i; source.second = j;
	    printf("%3d ", value_at_vertex_graph(a_graph, source));
	}
	printf("\n");
    }

    //Cleaning BFS
    BFS_reset_distance_graph(a_graph);
    printf("After BFS clean:\n");

    printf("    ");
    for (int j = 0 ; j < COLS ; j++)
	printf("%3d ", j);
    printf("\n");

    for (int i = 0 ; i < ROWS ; i++)
    {
	printf("%3d:", i);
	for (int j = 0 ; j < COLS ; j++)
	{
	    source.first = i; source.second = j;
	    printf("%3d ", value_at_vertex_graph(a_graph, source));
	}
	printf("\n");
    }

#undef ROWS
#undef COLS

#define ROWS 4
#define COLS 7

    //Another graph to test
    delete_graph(a_graph);
    a_graph = create_graph(ROWS, COLS);

    //Testing Initial graph
    printf("Another graph:\n");
    for (int i = 0 ; i < ROWS ; i++)
    {
	for (int j = 0 ; j < COLS ; j++)
	{
	    source.first = i; source.second = j;
	    printf("%d ", value_at_vertex_graph(a_graph, source));
	}
	printf("\n");
    }

    printf("Creating edges\n");
    for (int i = 0 ; i < ROWS ; i++)
    {
	for (int j = 0 ; j < COLS ; j++)
	{
	    if (j == 6) continue;
	    if (i == 0 && j == 4) continue;
	    if (i == 0 && j == 5) continue;
	    if (i == 0 && j == 6) continue;
	    if (i == 1 && j == 4) continue;
	    if (i == 2 && j == 4) continue;
/*
	    if (destination.second == 4 &&
		destination.first == 0) continue;

	    if (destination.second == 5 &&
		destination.first == 0) continue;

	    if (destination.second == 6 &&
		destination.first == 0) continue;

	    if (destination.second == 4 &&
		destination.first == 1) continue;

	    if (destination.second == 4 &&
		destination.first == 2) continue;
*/
	    source.first = i; source.second = j;

	    //Up
	    destination.first = (i - 1);
	    destination.second = (j);
	    destination.first = mod(destination.first, ROWS);
	    destination.second = mod(destination.second, COLS);
	    if (destination.second == 6) continue;

	    if (destination.second == 4 &&
		destination.first == 0) continue;

	    if (destination.second == 5 &&
		destination.first == 0) continue;

	    if (destination.second == 6 &&
		destination.first == 0) continue;

	    if (destination.second == 4 &&
		destination.first == 1) continue;

	    if (destination.second == 4 &&
		destination.first == 2) continue;


	    insert_edge_graph(a_graph, source, destination);

	    //Left
	    destination.first = (i) % ROWS;
	    destination.second = (j - 1) % COLS;
	    destination.first = mod(destination.first, ROWS);
	    destination.second = mod(destination.second, COLS);
	    if (destination.second == 6) continue;

	    if (destination.second == 4 &&
		destination.first == 0) continue;

	    if (destination.second == 5 &&
		destination.first == 0) continue;

	    if (destination.second == 6 &&
		destination.first == 0) continue;

	    if (destination.second == 4 &&
		destination.first == 1) continue;

	    if (destination.second == 4 &&
		destination.first == 2) continue;


	    insert_edge_graph(a_graph, source, destination);

	    //Down
	    destination.first = (i + 1) % ROWS;
	    destination.second = (j) % COLS;
	    destination.first = mod(destination.first, ROWS);
	    destination.second = mod(destination.second, COLS);
	    if (destination.second == 6) continue;

	    if (destination.second == 4 &&
		destination.first == 0) continue;

	    if (destination.second == 5 &&
		destination.first == 0) continue;

	    if (destination.second == 6 &&
		destination.first == 0) continue;

	    if (destination.second == 4 &&
		destination.first == 1) continue;

	    if (destination.second == 4 &&
		destination.first == 2) continue;


	    insert_edge_graph(a_graph, source, destination);

	    //Right
	    destination.first = (i) % ROWS;
	    destination.second = (j + 1) % COLS;
	    destination.first = mod(destination.first, ROWS);
	    destination.second = mod(destination.second, COLS);
	    if (destination.second == 6) continue;

	    if (destination.second == 4 &&
		destination.first == 0) continue;

	    if (destination.second == 5 &&
		destination.first == 0) continue;

	    if (destination.second == 6 &&
		destination.first == 0) continue;

	    if (destination.second == 4 &&
		destination.first == 1) continue;

	    if (destination.second == 4 &&
		destination.first == 2) continue;


	    insert_edge_graph(a_graph, source, destination);
	}
    }


    source.first = 0; source.second = 0;
    destination.first = 1; destination.second = 5;
    printf("Source:	    (%d,%d)\n", source.first, source.second);
    printf("Destination:    (%d,%d)\n", destination.first, destination.second);

    //Testing BFS
    BFS_fill_distance_graph(a_graph, source, destination);

    printf("After BFS:\n");

    printf("    ");
    for (int j = 0 ; j < COLS ; j++)
	printf("%3d ", j);
    printf("\n");

    for (int i = 0 ; i < ROWS ; i++)
    {
	printf("%3d:", i);
	for (int j = 0 ; j < COLS ; j++)
	{
	    source.first = i; source.second = j;
	    printf("%3d ", value_at_vertex_graph(a_graph, source));
	}
	printf("\n");
    }

    //Cleaning BFS
    BFS_reset_distance_graph(a_graph);
    printf("After BFS clean:\n");

    printf("    ");
    for (int j = 0 ; j < COLS ; j++)
	printf("%3d ", j);
    printf("\n");

    for (int i = 0 ; i < ROWS ; i++)
    {
	printf("%3d:", i);
	for (int j = 0 ; j < COLS ; j++)
	{
	    source.first = i; source.second = j;
	    printf("%3d ", value_at_vertex_graph(a_graph, source));
	}
	printf("\n");
    }

    delete_graph(a_graph);
    return 0;
}
