#include <stdlib.h>
#include "GraphX.h"
#include "QueueX.h"

/* nota con "d" en los nodos:
 * 0 - arriba
 * 1 - derecha
 * 2 - abajo
 * 3 - izquierda
 */

Cola Q;

void BFS(graph* G)
{
	
	G->start->d = 117; // <------ !!!
	G->start->color = 1;
	G->start->anterior = NULL;
	CreaCola(&Q);
	AgregaCola(&Q, (void*) G->start);
	
	node* u;
	while(!ColaVacia(&Q))
	{
		u = (node*) RetiraCola(&Q);
		int i;
		node* v;
		for(i = 0; i < 4 ; i++)
		{
			v = u->vecinos[i];
			if (v == NULL) continue;
			if (v->color == 0)
			{
				v->color == 1;
				v->d = (i + 2) % 4;
				v->anterior = u;
				AgregaCola(&Q, (void*) v);
			}
		}
		u->color = 2;
	}
}

void visit(node* u)
{
	u->color = 1;
	int i;
	for(i = 0; i < 4; i++)
	{
		node* v;
		v = u->vecinos[i];
		if(v == NULL) continue;
		if(v->color == 0)
		{
			v->anterior = u;
			visit(v);
		}
	}
	u->color = 2;
}

void DFS(graph* G)
{
	visit(G->start);
}



