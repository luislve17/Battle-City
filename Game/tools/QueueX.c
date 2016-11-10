#include <stdlib.h>
#include <stdio.h>

#define MAX_SPACE 1000 //Macro que define el tamaño maximo de cada estructura


struct Cola
{
    void* Q[MAX_SPACE];
    int inicio;
    int final;
    int tamano;
};

typedef struct Cola Cola;

void CreaCola(Cola *Q);
int ColaVacia(Cola *Q);
int ColaLlena(Cola *Q);
void AgregaCola(Cola *Q, void* x);
void* RetiraCola(Cola *Q);
int TamanoCola(Cola *Q);

void CreaCola(Cola *Q)
{
    Q->inicio = MAX_SPACE - 1;
    Q->final = 0;
    Q->tamano = 0;
}
int ColaVacia(Cola *Q)
{
    return Q -> tamano == 0;
}
int ColaLlena(Cola *Q)
{
    return Q -> tamano == MAX_SPACE;
}
void AgregaCola(Cola *Q, void* x)
{
    if (ColaLlena(Q))
    {
       printf("Cola llena, no se puede agregar\n");
       return;
    }
    Q->Q[Q->final] = x;
    Q->final++;
    Q->tamano++;
    Q->final %= MAX_SPACE;
    
}


void* RetiraCola(Cola *Q)
{
    if (ColaVacia(Q))
    {
        printf("Cola vacia, no se puede retirar\n");
        return NULL;
    }
    Q->inicio++;
	Q->inicio %= MAX_SPACE;
	Q->tamano--;
    return Q -> Q[Q->inicio];
}

int TamanoCola(Cola *Q)
{
    return Q->tamano;
}

