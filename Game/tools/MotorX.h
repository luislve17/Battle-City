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

void resetEnemigos();
bool addEnemigo(coordenada pos_inic);
void movRandom(tanque *T, int nivel);
void movRandomEnemigos();
void inicJuego(int nivel_inic);

void movTanqueArriba(tanque *T, int nivel);
void movTanqueDerecha(tanque *T, int nivel);
void movTanqueAbajo(tanque *T, int nivel);
void movTanqueIzquierda(tanque *T, int nivel);

bool colisionTArriba(tanque t1, tanque t2);
bool colisionTDerecha(tanque t1, tanque t2);
bool colisionTAbajo(tanque t1, tanque t2);
bool colisionTIzquierda(tanque t1, tanque t2);

char** setUnidad(char var, char ** MatrizNivel, int i, int j);
char** setTanque(tanque T, char **MatrizEntidades);

#endif
