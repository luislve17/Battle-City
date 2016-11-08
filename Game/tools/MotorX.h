#ifndef MOTORX_H
#define MOTORX_H

typedef struct{
	int pox;
	int poy;
	int vida;
	int poder;
	int orientacion;
}tanque;

tanque Jugador;
int game_over;

void test();
char** setUnidad(char var, char ** MatrizNivel, int i, int j);
char** setTanque(tanque T, char **MatrizNivel, int i, int j);
char** defMatNivel(char **MatrizModelo, int dim_modelo);
void printMat(char ** Mat, int dim);
void printNivel(char** MatrizNivel, int dim_Nivel);
int ejecutarEnNivel(int nivel);

#endif
