#ifndef MOTORX_H
#define MOTORX_H

#include "NivelesX.h"
#include "GraphX.h"

typedef enum { false, true } bool;

typedef struct{
	coordenada posic;
	int vida;
	int poder;
	int orientacion;
	bool vivo;
	int agresividad; // probabilidad de que dispare (en %)
}tanque;

typedef struct{
	coordenada posic;
	int orientacion;//1:Arriba, 2: Derecha, 3: Abajo, 4: Izquierda
	bool vivo;
}proyectil;

tanque Jugador;
tanque Enemigo[4];
proyectil Bala[8];
bool game_over;
int ticks;//Controlador de tiempo de spawn de enemigos

char** defMatNivel(char **MatrizModelo, int dim_modelo);
char** actualMatNivel(char** MatrizNivel, char** MatModelo, int dim_modelo);
char** inicMatEntidades(int dim_modelo);
char** actualMatEntidades(char** MatEntidades, int dim);

void printMat(char ** Mat, int dim);
void printNivel(char** MatrizNivel, char** MatrizEntidades, int dim_Nivel);
int ejecutarEnNivel(int nivel);

void resetEnemigos();
bool addEnemigo(coordenada pos_inic);

void resetBalas();
bool addBala(coordenada pos_inic, int dir);

void movRandom(tanque *T, int nivel);
void movRandomEnemigos(int nivel);
void inicJuego(int nivel_inic);

void movBFSEnemigos(graph* G, int nivel);
void movBFS(graph* G, tanque *T, int nivel);

void movTanqueArriba(tanque *T, int nivel);
void movTanqueDerecha(tanque *T, int nivel);
void movTanqueAbajo(tanque *T, int nivel);
void movTanqueIzquierda(tanque *T, int nivel);

void movBalas(int nivel);
void movProyectil(proyectil *p, int nivel);

bool colisionTArriba(tanque t1, tanque t2);
bool colisionTDerecha(tanque t1, tanque t2);
bool colisionTAbajo(tanque t1, tanque t2);
bool colisionTIzquierda(tanque t1, tanque t2);

void movProyArriba(proyectil *p, int nivel);
void movProyDerecha(proyectil *p, int nivel);
void movProyAbajo(proyectil *p, int nivel);
void movProyIzquierda(proyectil *p, int nivel);

char** setUnidad(char var, char ** MatrizNivel, int i, int j);
char** setTanque(tanque T, char **MatrizEntidades);
char** setProyectil(proyectil bala, char** MatrizEntidades);

#endif
