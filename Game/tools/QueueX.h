#ifndef QUEUE_H
#define QUEUE_H

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


#endif
