#ifndef NIVELESX_H
#define NIVELESX_H

#include <stdio.h>
#include <stdlib.h>
#include "NivelesX.h"
#include <string.h>
#include "UtilX.h"

typedef struct{
	int x, y;
}coordenada;

typedef struct{
	char** MatModelo;
	int dim;
	char *idClave;
	coordenada jug_inic;
	coordenada spawns[3];
	int cant_spawns;
}Nivel;

Nivel* Niveles;
int totalNiveles;

void cargarNiveles();
void descargarNiveles();
coordenada genCoord(int a, int b);
int sonEquiv(char* p1, char* p2);
int buscarNivelxClave(char* claveIngresada);

#endif
