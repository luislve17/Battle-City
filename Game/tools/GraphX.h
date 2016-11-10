#ifndef GRAPH_H
#define GRAPH_H

#include "NivelesX.h"
#include <stdlib.h>

typedef struct node node;
struct node
{
    node* vecinos[4]; // NESW
    int color; // 0 no visitado, 1 visitado // 100 optimo
    node* anterior;
    int d;
};

typedef struct graph graph;
struct graph
{
    node** matrix;
    int w;
    int h;
    node* start;
    node* end;
};

graph* getMapGraph(Nivel* map);
void deleteGraph(graph* G);
void resetGraph(graph* G, Nivel* map);
void paintPath(graph* G);

#endif
