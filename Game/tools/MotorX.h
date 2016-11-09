#ifndef MOTORX_H
#define MOTORX_H

#include "NivelesX.h"

typedef enum { false, true } bool;

typedef struct{
	coordenada posic;
	int vida;
	int poder;
	int orientacion;
}tanque;

tanque Jugador;
tanque Enemigo[4];
bool game_over;
int ticks;//Controlador de tiempo de spawn de enemigos

char** defMatNivel(char **MatrizModelo, int dim_modelo);
char** inicMatEntidades(int dim_modelo);
char** actualMatEntidades(char** MatEntidades, int dim);

void printMat(char ** Mat, int dim);
void printNivel(char** MatrizNivel, char** MatrizEntidades, int dim_Nivel);
int ejecutarEnNivel(int nivel);

void inicEnemigos();
bool addEnemigo(coordenada pos_inic);
//void movRandomEnemigos();
void inicJuego(int nivel_inic);

void movJugadorArriba(int nivel);
void movJugadorDerecha(int nivel);
void movJugadorAbajo(int nivel);
void movJugadorIzquierda(int nivel);

char** setUnidad(char var, char ** MatrizNivel, int i, int j);
char** setTanque(tanque T, char **MatrizEntidades);

#endif
