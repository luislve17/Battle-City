#include "NivelesX.h"
#include <stdlib.h>

typedef struct node node;
struct node
{
    node* vecinos[4]; // NESW
    int color; // 0 blanco, 1 gris, 2 negro, 3 optimo (se dibujara)
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

graph* getMapGraph(Nivel* map)
{
    graph* G = (graph*) calloc(1, sizeof(graph));
    G -> matrix = (node**) calloc(map->dim, sizeof(node*));
    node* data = (node*) calloc(map->dim * map->dim, sizeof(node));
    G->w = map->dim;
    G->h = map->dim;
    int i, j;
    for(i = 0; i < G->h; i++)
    {
        G -> matrix[i] = data + i*G->w;
    }
    
    for(i = 0; i < G -> h; i++) //fila
    {
        for(j = 0; j < G -> w; j++) //columna
        {
            if(i>0 && map->MatModelo[i-1][j] != 'p' && map->MatModelo[i-1][j] != 'a') // añadir nodo norte
            {
            	G->matrix[i][j].vecinos[0] = &(G->matrix[i-1][j]);
            }
            else G->matrix[i][j].vecinos[0] = NULL;
            
            if(j< G->w-1 && map->MatModelo[i][j+1] != 'p' && map->MatModelo[i][j+1] != 'a') // añadir nodo este
            {
            	G->matrix[i][j].vecinos[1] = &(G->matrix[i][j+1]);
            }
            else G->matrix[i][j].vecinos[1] = NULL;
            
            if(i< G->h-1 && map->MatModelo[i+1][j] != 'p' && map->MatModelo[i+1][j] != 'a') // añadir nodo sur
            {
            	G->matrix[i][j].vecinos[2] = &(G->matrix[i+1][j]);
            }
            else G->matrix[i][j].vecinos[2] = NULL;
            
            if(j>0 && map->MatModelo[i][j-1] != 'p' && map->MatModelo[i][j-1] != 'a') // añadir nodo oeste
            {
            	G->matrix[i][j].vecinos[3] = &(G->matrix[i][j-1]);
            }
            else G->matrix[i][j].vecinos[3] = NULL;
            
            if(map->MatModelo[i][j] == 'j')
            {
            	G->start = &(G->matrix[i][j]);
            }
            
        }
        
    }
    
    return G;
}

void deleteGraph(graph* G)
{
	free(G->matrix[0]);
	free(G->matrix);
	free(G);
}

void resetGraph(graph* G, Nivel* map)
{
	int i, j;
    for(i = 0; i < G -> h; i++) //fila
    {
        for(j = 0; j < G -> w; j++) //columna
        {
            G->matrix[i][j].color = 0; // blanco
            G->matrix[i][j].anterior = NULL;
            G->matrix[i][j].d = -1; //"infinito"
            
            if(map->MatModelo[i][j] == 'j')
            {
            	G->start = &(G->matrix[i][j]);
            }
        }
        
    }

}

void paintPath(graph* G)
{
	node* t = G->end;
	while(t != NULL)
	{
		t->color = 3;
		t = t->anterior;
	}
}

