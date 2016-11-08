#include <stdio.h>
#include <stdlib.h>
#include "MotorX.h"
#include "InputX.h"
#include "AnimX.h"
#include "NivelesX.h"

#define NORM  "\x1B[0m"
#define ROJO  "\x1B[31m"
#define VERD  "\x1B[32m"
#define AMAR  "\x1B[33m"
#define AZUL  "\x1B[34m"
#define MAGN  "\x1B[35m"
#define CYAN  "\x1B[36m"
#define BLNC  "\x1B[37m"

void test(){
	cargarNiveles();
	ejecutarEnNivel(1);
}

char** defMatNivel(char **MatrizModelo, int dim_modelo){
	int i, j;
	
	char ch, **MatrizNivel;
	MatrizNivel = (char**)calloc(3*dim_modelo,sizeof(char*));
	for(i = 0; i < 3*dim_modelo; i++){
		MatrizNivel[i] = (char*)calloc(3*dim_modelo,sizeof(char));
	}
	
	for(i = 0; i < dim_modelo; i++){
		for(j = 0; j < dim_modelo; j++){
			ch = MatrizModelo[i][j];
			switch(ch){
				case 'j':
					MatrizNivel = setTanque(Jugador, MatrizNivel, i, j);
					break;
				case 'c':
					MatrizNivel = setUnidad('*', MatrizNivel, i, j);
					break;
				case 'p':
					MatrizNivel = setUnidad('#', MatrizNivel, i, j);
					break;
				case 'a':
					MatrizNivel = setUnidad('~', MatrizNivel, i, j);
					break;
				case 'v':
					MatrizNivel = setUnidad(' ', MatrizNivel, i, j);
					break;
				case 's':
					MatrizNivel = setUnidad('@', MatrizNivel, i, j);
					break;
			}
		}
	}
	return MatrizNivel;
}

void printMat(char ** Mat, int dim){
	int i, j;
	for(i = 0; i < dim; i++){
		for(j = 0; j < dim; j++){
			printf(" %c ", Mat[i][j]);
		}
		printf("\n");
	}
}

void printNivel(char** MatrizNivel, int dim_Nivel){
	int i, j;
	char aux;
	printf("VIDA: %d\n", Jugador.vida);
	printf("PODER: %d\n", Jugador.poder);
	for(i = 0; i < dim_Nivel; i++){
		for(j = 0; j < dim_Nivel; j++){
			aux = MatrizNivel[i][j];
			if(aux == '*'){
				printf(VERD " %c " NORM,aux);
			}
			else if(aux == '~'){
				printf(CYAN " %c " NORM,aux);
			}
			else if(aux == '#'){
				printf(ROJO " %c " NORM,aux);
			}
			else{
				printf(NORM " %c " NORM, aux);
			}
		}
		printf("\n");
	}
}

char** setUnidad(char var, char ** MatrizNivel, int i, int j){
	//Función que llenará unidades en la matriz escalada del nivel actual
	int aux1, aux2;
	for(aux1 = 3*i; aux1 <= 3*i + 2; aux1++){
		for(aux2 = 3*j; aux2 <= 3*j + 2; aux2++){
			MatrizNivel[aux1][aux2] = var;
		}
	}
	return MatrizNivel;
}

char** setTanque(tanque T, char **MatrizNivel, int i, int j){
	switch(T.orientacion){
		case 1://Arriba
			/*
			d^b
			|8|
			d-b
			*/
			MatrizNivel[3*i][3*j] = 'd';
			MatrizNivel[3*i][3*j + 1] = '^';
			MatrizNivel[3*i][3*j + 2] = 'b';
			MatrizNivel[3*i + 1][3*j] = '|';
			MatrizNivel[3*i + 1][3*j + 1] = '8';
			MatrizNivel[3*i + 1][3*j + 2] = '|';
			MatrizNivel[3*i + 2][3*j] = 'd';
			MatrizNivel[3*i + 2][3*j + 1] = '-';
			MatrizNivel[3*i + 2][3*j + 2] = 'b';
			break;
		case 2://Derecha
			/*
			o-o
			|8>
			o-o
			*/
			MatrizNivel[3*i][3*j] = 'o';
			MatrizNivel[3*i][3*j + 1] = '-';
			MatrizNivel[3*i][3*j + 2] = 'o';
			MatrizNivel[3*i + 1][3*j] = '|';
			MatrizNivel[3*i + 1][3*j + 1] = '8';
			MatrizNivel[3*i + 1][3*j + 2] = '>';
			MatrizNivel[3*i + 2][3*j] = 'o';
			MatrizNivel[3*i + 2][3*j + 1] = '-';
			MatrizNivel[3*i + 2][3*j + 2] = 'o';
			break;
		case 3://Abajo
			/*
			d-b
			|8|
			dvb
			*/
			MatrizNivel[3*i][3*j] = 'd';
			MatrizNivel[3*i][3*j + 1] = '-';
			MatrizNivel[3*i][3*j + 2] = 'b';
			MatrizNivel[3*i + 1][3*j] = '|';
			MatrizNivel[3*i + 1][3*j + 1] = '8';
			MatrizNivel[3*i + 1][3*j + 2] = '|';
			MatrizNivel[3*i + 2][3*j] = 'd';
			MatrizNivel[3*i + 2][3*j + 1] = 'v';
			MatrizNivel[3*i + 2][3*j + 2] = 'b';
			break;
		case 4://Izquierda
			/*
			o-o
			<8|
			o-o
			*/
			MatrizNivel[3*i][3*j] = 'o';
			MatrizNivel[3*i][3*j + 1] = '-';
			MatrizNivel[3*i][3*j + 2] = 'o';
			MatrizNivel[3*i + 1][3*j] = '<';
			MatrizNivel[3*i + 1][3*j + 1] = '8';
			MatrizNivel[3*i + 1][3*j + 2] = '|';
			MatrizNivel[3*i + 2][3*j] = 'o';
			MatrizNivel[3*i + 2][3*j + 1] = '-';
			MatrizNivel[3*i + 2][3*j + 2] = 'o';
			break;
	}
	return MatrizNivel;
}

int ejecutarEnNivel(int nivel){
	char ** MatNv;
	
	Jugador.pox = Niveles[nivel].jug_inic.x;
	Jugador.poy = Niveles[nivel].jug_inic.y;
	Jugador.orientacion = rand()%4 + 1; //Orientacion aleatoria
		
	MatNv = defMatNivel(Niveles[nivel].MatModelo, Niveles[nivel].dim);
	char key;
	char temp = 'v';
	while(1){
		printNivel(MatNv, 3*(Niveles[nivel].dim));
		key = getKeyInput();
		if(key == 'A'){
			if((Jugador.pox > 0)&&(Niveles[nivel].MatModelo[Jugador.pox - 1][Jugador.poy] != 'p')&&(((Niveles[nivel].MatModelo[Jugador.pox - 1][Jugador.poy] != 'a'))||(Jugador.poder == 1))){
				Niveles[nivel].MatModelo[Jugador.pox][Jugador.poy] = temp;
				temp = Niveles[nivel].MatModelo[Jugador.pox - 1][Jugador.poy];
				Jugador.pox--;
			}
			Jugador.orientacion = 1;
		}
		else if(key == 'C'){
			if((Jugador.poy < Niveles[nivel].dim - 1)&&(Niveles[nivel].MatModelo[Jugador.pox][Jugador.poy + 1] != 'p')&&(((Niveles[nivel].MatModelo[Jugador.pox][Jugador.poy + 1] != 'a'))||(Jugador.poder == 1))){
				Niveles[nivel].MatModelo[Jugador.pox][Jugador.poy] = temp;
				temp = Niveles[nivel].MatModelo[Jugador.pox][Jugador.poy + 1];
				Jugador.poy++;
			}
			Jugador.orientacion = 2;
		}
		else if(key == 'B'){
			if((Jugador.pox < Niveles[nivel].dim - 1)&&(Niveles[nivel].MatModelo[Jugador.pox + 1][Jugador.poy] != 'p')&&(((Niveles[nivel].MatModelo[Jugador.pox + 1][Jugador.poy] != 'a'))||(Jugador.poder == 1))){
				Niveles[nivel].MatModelo[Jugador.pox][Jugador.poy] = temp;
				temp = Niveles[nivel].MatModelo[Jugador.pox + 1][Jugador.poy];
				Jugador.pox++;
			}
			Jugador.orientacion = 3;
		}
		else if(key == 'D'){
			if((Jugador.poy > 0)&&(Niveles[nivel].MatModelo[Jugador.pox][Jugador.poy - 1] != 'p')&&(((Niveles[nivel].MatModelo[Jugador.pox][Jugador.poy - 1] != 'a'))||(Jugador.poder == 1))){
				Niveles[nivel].MatModelo[Jugador.pox][Jugador.poy] = temp;
				temp = Niveles[nivel].MatModelo[Jugador.pox][Jugador.poy - 1];
				Jugador.poy--;
			}
			Jugador.orientacion = 4;
		}
		else if(key == '1'){
			Jugador.poder = (Jugador.poder + 1)%2;
		}
		else if(key == '2'){
			Jugador.vida++;
		}
		else if(key == '\n'){//Nivel finalizado
			return 1;
		}
		else if(key == 'q'){//Personaje derrotado o equivalente
			game_over = 1;
			return 0;
		}
		limpOut(3*(Niveles[nivel].dim) + 2);
		Niveles[nivel].MatModelo[Jugador.pox][Jugador.poy] = 'j';
		MatNv = defMatNivel(Niveles[nivel].MatModelo, Niveles[nivel].dim);
	}
}
