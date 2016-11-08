#include <stdio.h>
#include "map.h"
#include "graph.h"

#define RED           "\x1b[31m"
#define BLUE          "\x1b[34m"
#define MAGENTA       "\x1b[35m"
#define COLOR_RESET   "\x1b[0m"

const char MAP_CHARACTERS[] = " #8D"; // 0 vacio, 1 pared, 2, raton, 3 queso

void printMap (Map* map, graph* G1, graph* G2)
{
    printf("\033[2;0H");
    
    int i,j;
    for(i = 0; i < map -> h; i++)
    {
        for(j = 0; j < map -> w; j++)
        {
            if(G1->matrix[i][j].color == 3 && G2->matrix[i][j].color != 3 && map -> matrix[i][j] == 0)
            {
            	printf(RED "x" COLOR_RESET);
            	continue;
            }
            
            if(G1->matrix[i][j].color != 3 && G2->matrix[i][j].color == 3 && map -> matrix[i][j] == 0)
            {
            	printf(BLUE "x" COLOR_RESET);
            	continue;
            }
            
            if(G1->matrix[i][j].color == 3 && G2->matrix[i][j].color == 3 && map -> matrix[i][j] == 0)
            {
            	printf(MAGENTA "x" COLOR_RESET);
            	continue;
            }
            
            printf("%c", MAP_CHARACTERS[map -> matrix[i][j]]);
        }
        printf("\n");
    }
    printf("Controles : i,j,k,l para moverse, q para salir\n\n" COLOR_RESET);
    printf("8 : raton			D : queso\n");
    printf(RED "Camino BFS en ROJO\n" COLOR_RESET);
    printf(BLUE "Camino DFS en AZUL\n" COLOR_RESET);
    
}

