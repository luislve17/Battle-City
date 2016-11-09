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

char** defMatNivel(char **MatrizModelo, int dim_modelo){//La matriz de nivel solo almacena terreno y no entidades
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

char** inicMatEntidades(int dim_modelo){
	char** MatEntidades = (char**)malloc(3*dim_modelo*sizeof(char*));
	int i, j;
	for(i = 0; i < 3*dim_modelo; i++){
		MatEntidades[i] = (char*)malloc(sizeof(char)*3*dim_modelo);
	}
	for(i = 0; i < 3*dim_modelo; i++){
		for(j = 0; j < 3*dim_modelo; j++){
			MatEntidades[i][j] = '\0';
		}
	}
	return MatEntidades;
}

char** actualMatEntidades(char** MatEntidades, int dim){
	int i, j;
	for(i = 0; i < dim; i++){
		for(j = 0; j < dim; j++){
			MatEntidades[i][j] = '\0';
		}
	}
	MatEntidades = setTanque(Jugador, MatEntidades);
	return MatEntidades;
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

void printNivel(char** MatrizNivel, char** MatrizEntidades, int dim_Matriz){
	int i, j;
	char aux1, aux2;
	printf("VIDA: %d\n", Jugador.vida);
	printf("PODER: %d\n", Jugador.poder);
	printf("TICK: %d\n", ticks);
	for(i = 0; i < dim_Matriz; i++){
		for(j = 0; j < dim_Matriz; j++){
			aux1 = MatrizNivel[i][j];
			aux2 = MatrizEntidades[i][j];
			if(aux2 == '\0'){
				if(aux1 == '*'){
					printf(VERD " %c " NORM,aux1);
				}
				else if(aux1 == '~'){
					printf(CYAN " %c " NORM,aux1);
				}
				else if(aux1 == '#'){
					printf(ROJO " %c " NORM,aux1);
				}
				else{
					printf(NORM " %c " NORM, aux1);
				}
			}
			else{
				printf(" %c ", aux2);
			}
		}
		printf("\n");
	}
}

int ejecutarEnNivel(int nivel){
	char ** MatNv, ** MatEnti;
	
	MatNv = defMatNivel(Niveles[nivel].MatModelo, Niveles[nivel].dim);
	MatEnti = inicMatEntidades(Niveles[nivel].dim);
	
	Jugador.posic = Niveles[nivel].jug_inic;
	Jugador.orientacion = rand()%4 + 1; //Orientacion aleatoria

	MatEnti = actualMatEntidades(MatEnti, 3*Niveles[nivel].dim);
	char key;
	
	ticks = 0;//Inicializamos los ticks
	//inicEnemigos();//Inicializamos los enemigos
	while(1){
		printNivel(MatNv, MatEnti, 3*(Niveles[nivel].dim));
		key = getKeyInput();
		if(key == 'A'){
			movJugadorArriba(nivel);
		}
		else if(key == 'C'){
			movJugadorDerecha(nivel);
		}
		else if(key == 'B'){
			movJugadorAbajo(nivel);
		}
		else if(key == 'D'){
			movJugadorIzquierda(nivel);
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
		ticks = (ticks + 1)%30;//Los ticks del juego irán del 0 al 49 por cada movimiento y se reiniciarán
		
/*		if(ticks == 0){*/
/*			int enemigoGenerado = 0;//Flag que revisa si se generó un enemigo satisfactoriamente*/
/*			while(!enemigoGenerado){*/
/*				int elegirSpawn = rand()%3;//Elegimos aleatoriamente donde se generará el enemigo*/
/*				enemigoGenerado = addEnemigo(Niveles[nivel].spawns[elegirSpawn]);*/
/*			}*/
/*		}*/
/*		movRandomEnemigos(Niveles[nivel]);*/
		limpOut(3*(Niveles[nivel].dim) + 3);
/*		for(int i = 0; i < 4; i++){*/
/*			if(Enemigo[i].posic.x != -1){*/
/*				Niveles[nivel].MatModelo[Enemigo[i].posic.x][Enemigo[i].posic.y] = 't';*/
/*			}*/
/*		}*/
		//De momento solo se actualizan las entidades, pero el terreno también deberá
		MatEnti = actualMatEntidades(MatEnti, 3*(Niveles[nivel].dim));
	}
}


void inicEnemigos(){
	int i;
	for(i = 0; i < 4; i++){
		//Coordenadas en -1,-1 indican que el enemigo no ha sido creado de por sí
		Enemigo[i].posic = genCoord(-1,-1);
	}
}

bool addEnemigo(coordenada pos_inic){
	int i = 0;
	while((i < 4)&&(Enemigo[i].posic.x != -1)){
		i++;
	}
	if(Enemigo[i].posic.x == -1){
	//En el primer espacio disponible vacío para agregar un nuevo enemigo
		Enemigo[i].posic = pos_inic;
		Enemigo[i].vida = 3;
		Enemigo[i].orientacion = rand()%4 + 1;
		return true;//Generacion de enemigo exitosa
	}
	return false;//Generacion de enemigo no exitosa
}

/*void movRandomEnemigos(Nivel niv){*/
/*	int i;*/
/*	for(i = 0; i < 4; i++){//Temporalmente, 4 es el numero máximo de enemigos por nivel*/
/*		if(Enemigo[i].posic.x != -1){ */
/*			int delta = (rand()%4);*/
/*			if(delta == 0){//arriba*/
/*				if((Enemigo[i].posic.x > 0)&&(niv.MatModelo[Enemigo[i].posic.x - 1][Enemigo[i].posic.y] != 'p')){*/
/*					niv.MatModelo[Enemigo[i].posic.x][Enemigo[i].posic.y] = Enemigo[i].piso;*/
/*					Enemigo[i].piso =  niv.MatModelo[Enemigo[i].posic.x - 1][Enemigo[i].posic.y];*/
/*					Enemigo[i].posic.x--;*/
/*				}*/
/*				Enemigo[i].orientacion = 1;*/
/*			}*/
/*			else if(delta == 1){//derecha*/
/*				if((Enemigo[i].posic.y < niv.dim - 1)&&(niv.MatModelo[Enemigo[i].posic.x][Enemigo[i].posic.y + 1] != 'p')){*/
/*					niv.MatModelo[Enemigo[i].posic.x][Enemigo[i].posic.y] = Enemigo[i].piso;*/
/*					Enemigo[i].piso = niv.MatModelo[Enemigo[i].posic.x][Enemigo[i].posic.y + 1];*/
/*					Enemigo[i].posic.y++;*/
/*				}*/
/*				Enemigo[i].orientacion = 2;*/
/*			}*/
/*			else if(delta == 2){//abajo*/
/*				if((Enemigo[i].posic.x < niv.dim - 1)&&(niv.MatModelo[Enemigo[i].posic.x + 1][Enemigo[i].posic.y] != 'p')){*/
/*					niv.MatModelo[Enemigo[i].posic.x][Enemigo[i].posic.y] = Enemigo[i].piso;*/
/*					Enemigo[i].piso = niv.MatModelo[Enemigo[i].posic.x + 1][Enemigo[i].posic.y];*/
/*					Enemigo[i].posic.x++;*/
/*				}*/
/*				Enemigo[i].orientacion = 3;*/
/*			}*/
/*			else if(delta == 3){//izquierda*/
/*				if((Enemigo[i].posic.y > 0)&&(niv.MatModelo[Enemigo[i].posic.x][Enemigo[i].posic.y - 1] != 'p')){*/
/*					niv.MatModelo[Enemigo[i].posic.x][Enemigo[i].posic.y] = Enemigo[i].piso;*/
/*					Enemigo[i].piso = niv.MatModelo[Enemigo[i].posic.x][Enemigo[i].posic.y - 1];*/
/*					Enemigo[i].posic.y--;*/
/*				}*/
/*				Enemigo[i].orientacion = 4;*/
/*			}*/
/*		}*/
/*	}*/
/*}*/

void inicJuego(int nivel_inic){
	game_over = 0;//Se inicializa el juego
	int nivel = nivel_inic;//Nivel inicial

	while((!game_over)&&(nivel < totalNiveles)){//Se irán acumulando los niveles sumando al game_over
		limpOut(3*(Niveles[nivel].dim) + 2);
		nivel += ejecutarEnNivel(nivel);
	}
}

//<funciones de movimiento>
void movJugadorArriba(int nivel){
	if((Jugador.posic.x > 0)&&(Niveles[nivel].MatModelo[Jugador.posic.x - 1][Jugador.posic.y] != 'p')&&(((Niveles[nivel].MatModelo[Jugador.posic.x - 1][Jugador.posic.y] != 'a'))||(Jugador.poder == 1))){
				Jugador.posic.x--;
			}
			Jugador.orientacion = 1;
}

void movJugadorDerecha(int nivel){
	if((Jugador.posic.y < Niveles[nivel].dim - 1)&&(Niveles[nivel].MatModelo[Jugador.posic.x][Jugador.posic.y + 1] != 'p')&&(((Niveles[nivel].MatModelo[Jugador.posic.x][Jugador.posic.y + 1] != 'a'))||(Jugador.poder == 1))){
				Jugador.posic.y++;
			}
			Jugador.orientacion = 2;
}

void movJugadorAbajo(int nivel){
	if((Jugador.posic.x < Niveles[nivel].dim - 1)&&(Niveles[nivel].MatModelo[Jugador.posic.x + 1][Jugador.posic.y] != 'p')&&(((Niveles[nivel].MatModelo[Jugador.posic.x + 1][Jugador.posic.y] != 'a'))||(Jugador.poder == 1))){
				Jugador.posic.x++;
			}
			Jugador.orientacion = 3;
}

void movJugadorIzquierda(int nivel){
	if((Jugador.posic.y > 0)&&(Niveles[nivel].MatModelo[Jugador.posic.x][Jugador.posic.y - 1] != 'p')&&(((Niveles[nivel].MatModelo[Jugador.posic.x][Jugador.posic.y - 1] != 'a'))||(Jugador.poder == 1))){
				Jugador.posic.y--;
			}
			Jugador.orientacion = 4;
}
//</funciones de movimiento>

//<funciones visuales en matriz>
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

char** setTanque(tanque T, char **MatrizEntidades){
	switch(T.orientacion){
		case 1://Arriba
			/*
			d^b
			|8|
			d-b
			*/
			MatrizEntidades[3*T.posic.x][3*T.posic.y] = 'd';
			MatrizEntidades[3*T.posic.x][3*T.posic.y + 1] = '^';
			MatrizEntidades[3*T.posic.x][3*T.posic.y + 2] = 'b';
			MatrizEntidades[3*T.posic.x + 1][3*T.posic.y] = '|';
			MatrizEntidades[3*T.posic.x + 1][3*T.posic.y + 1] = '8';
			MatrizEntidades[3*T.posic.x + 1][3*T.posic.y + 2] = '|';
			MatrizEntidades[3*T.posic.x + 2][3*T.posic.y] = 'd';
			MatrizEntidades[3*T.posic.x + 2][3*T.posic.y + 1] = '-';
			MatrizEntidades[3*T.posic.x + 2][3*T.posic.y + 2] = 'b';
			break;
		case 2://Derecha
			/*
			o-o
			|8>
			o-o
			*/
			MatrizEntidades[3*T.posic.x][3*T.posic.y] = 'o';
			MatrizEntidades[3*T.posic.x][3*T.posic.y + 1] = '-';
			MatrizEntidades[3*T.posic.x][3*T.posic.y + 2] = 'o';
			MatrizEntidades[3*T.posic.x + 1][3*T.posic.y] = '|';
			MatrizEntidades[3*T.posic.x + 1][3*T.posic.y + 1] = '8';
			MatrizEntidades[3*T.posic.x + 1][3*T.posic.y + 2] = '>';
			MatrizEntidades[3*T.posic.x + 2][3*T.posic.y] = 'o';
			MatrizEntidades[3*T.posic.x + 2][3*T.posic.y + 1] = '-';
			MatrizEntidades[3*T.posic.x + 2][3*T.posic.y + 2] = 'o';
			break;
		case 3://Abajo
			/*
			d-b
			|8|
			dvb
			*/
			MatrizEntidades[3*T.posic.x][3*T.posic.y] = 'd';
			MatrizEntidades[3*T.posic.x][3*T.posic.y + 1] = '-';
			MatrizEntidades[3*T.posic.x][3*T.posic.y + 2] = 'b';
			MatrizEntidades[3*T.posic.x + 1][3*T.posic.y] = '|';
			MatrizEntidades[3*T.posic.x + 1][3*T.posic.y + 1] = '8';
			MatrizEntidades[3*T.posic.x + 1][3*T.posic.y + 2] = '|';
			MatrizEntidades[3*T.posic.x + 2][3*T.posic.y] = 'd';
			MatrizEntidades[3*T.posic.x + 2][3*T.posic.y + 1] = 'v';
			MatrizEntidades[3*T.posic.x + 2][3*T.posic.y + 2] = 'b';
			break;
		case 4://Izquierda
			/*
			o-o
			<8|
			o-o
			*/
			MatrizEntidades[3*T.posic.x][3*T.posic.y] = 'o';
			MatrizEntidades[3*T.posic.x][3*T.posic.y + 1] = '-';
			MatrizEntidades[3*T.posic.x][3*T.posic.y + 2] = 'o';
			MatrizEntidades[3*T.posic.x + 1][3*T.posic.y] = '<';
			MatrizEntidades[3*T.posic.x + 1][3*T.posic.y + 1] = '8';
			MatrizEntidades[3*T.posic.x + 1][3*T.posic.y + 2] = '|';
			MatrizEntidades[3*T.posic.x + 2][3*T.posic.y] = 'o';
			MatrizEntidades[3*T.posic.x + 2][3*T.posic.y + 1] = '-';
			MatrizEntidades[3*T.posic.x + 2][3*T.posic.y + 2] = 'o';
			break;
	}
	return MatrizEntidades;
}
//</funciones visuales en matriz>


