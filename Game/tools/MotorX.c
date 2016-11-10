#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
	for(i = 0; i < 4; i++){
		if((Enemigo[i].posic.x != -1)&&(Enemigo[i].vida > 0)){
			MatEntidades = setTanque(Enemigo[i], MatEntidades);
		}
	}
	return MatEntidades;
}

bool colisionTArriba(tanque t1, tanque t2){//Revisa si t2 está arriba de t1
	if((t1.posic.x - 1 == t2.posic.x)&&(t1.posic.y == t2.posic.y)){
		return true;
	}
	return false;
}

bool colisionTDerecha(tanque t1, tanque t2){//Revisa si t2 está arriba de t1
	if((t1.posic.x == t2.posic.x)&&(t1.posic.y + 1 == t2.posic.y)){
		return true;
	}
	return false;
}

bool colisionTAbajo(tanque t1, tanque t2){//Revisa si t2 está arriba de t1
	if((t1.posic.x + 1 == t1.posic.x)&&(t1.posic.y == t2.posic.y)){
		return true;
	}
	return false;
}

bool colisionTIzquierda(tanque t1, tanque t2){//Revisa si t2 está arriba de t1
	if((t1.posic.x == t2.posic.x)&&(t1.posic.y - 1 == t2.posic.y)){
		return true;
	}
	return false;
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
	int enemigosEnPantalla = 0;
	
	time_t t;
	
	MatNv = defMatNivel(Niveles[nivel].MatModelo, Niveles[nivel].dim);
	MatEnti = inicMatEntidades(Niveles[nivel].dim);
	
	Jugador.posic = Niveles[nivel].jug_inic;
	Jugador.orientacion = rand()%4 + 1; //Orientacion aleatoria

	MatEnti = actualMatEntidades(MatEnti, 3*Niveles[nivel].dim);
	char key;
	
	ticks = 0;//Inicializamos los ticks
	resetEnemigos();
	while(1){
		printNivel(MatNv, MatEnti, 3*(Niveles[nivel].dim));
		key = getKeyInput();
		if(key == 'A'){
			movTanqueArriba(&Jugador, nivel);
		}
		else if(key == 'C'){
			movTanqueDerecha(&Jugador, nivel);
		}
		else if(key == 'B'){
			movTanqueAbajo(&Jugador, nivel);
		}
		else if(key == 'D'){
			movTanqueIzquierda(&Jugador, nivel);
		}
		else if(key == '1'){
			Jugador.poder = (Jugador.poder + 1)%2;
		}
		else if(key == '2'){
			Jugador.vida++;
		}
		else if(key == '\n'){//Nivel finalizado
			break;
		}
		else if(key == 'q'){//Personaje derrotado o equivalente
			game_over = 1;
			return 0;
		}
		ticks = (ticks + 1)%30;//Los ticks del juego irán del 0 al 29 por cada movimiento y se reiniciarán
		
		if((ticks == 0)&&(enemigosEnPantalla < 4)){
			addEnemigo(Niveles[nivel].spawns[0]);
			enemigosEnPantalla++;
		}

		movRandomEnemigos(nivel);
		limpOut(3*(Niveles[nivel].dim) + 3);

		//De momento solo se actualizan las entidades, pero el terreno también deberá
		MatEnti = actualMatEntidades(MatEnti, 3*(Niveles[nivel].dim));
	}
	resetEnemigos();
	return 1;
}


void resetEnemigos(){
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

void movRandom(tanque *T, int nivel){
	time_t t;
	srand((unsigned)time(&t)*((*T).posic.x - ((*T).posic.y)*(Jugador.posic.x * (*T).posic.x)));
	
	int direccion = rand()%4;
	
	switch(direccion){
		case 0:
		movTanqueArriba(T, nivel);
		break;
		
		case 1:
		movTanqueDerecha(T, nivel);
		break;
		
		case 2:
		movTanqueAbajo(T, nivel);
		break;
		
		case 3:
		movTanqueIzquierda(T, nivel);
		break;
	}
}

void movRandomEnemigos(int nivel){
	int i;
	for(i = 0; i < 4; i++){
		if(Enemigo[i].posic.x != -1){
			movRandom(&(Enemigo[i]), nivel);
		}
	}
}

void inicJuego(int nivel_inic){
	game_over = 0;//Se inicializa el juego
	int nivel = nivel_inic;//Nivel inicial

	while((!game_over)&&(nivel < totalNiveles)){//Se irán acumulando los niveles sumando al game_over
		limpOut(3*(Niveles[nivel].dim) + 3);
		nivel += ejecutarEnNivel(nivel);
	}
}

//<funciones de movimiento>
void movTanqueArriba(tanque *T, int nivel){
	if(((*T).posic.x > 0)&&(Niveles[nivel].MatModelo[(*T).posic.x - 1][(*T).posic.y] != 'p')&&(!(colisionTArriba(*T, Enemigo[0])))&&(!(colisionTArriba(*T, Enemigo[1])))&&(!(colisionTArriba(*T, Enemigo[2])))&&(!(colisionTArriba(*T, Enemigo[3])))&&(!(colisionTArriba(*T, Jugador)))&&(((Niveles[nivel].MatModelo[(*T).posic.x - 1][(*T).posic.y] != 'a'))||((*T).poder == 1))){
				(*T).posic.x--;
			}
			(*T).orientacion = 1;
}

void movTanqueDerecha(tanque *T, int nivel){
	if(((*T).posic.y < Niveles[nivel].dim - 1)&&(Niveles[nivel].MatModelo[(*T).posic.x][(*T).posic.y + 1] != 'p')&&(!(colisionTDerecha(*T, Enemigo[0])))&&(!(colisionTDerecha(*T, Enemigo[1])))&&(!(colisionTDerecha(*T, Enemigo[2])))&&(!(colisionTDerecha(*T, Enemigo[3])))&&(!(colisionTDerecha(*T, Jugador)))&&(((Niveles[nivel].MatModelo[(*T).posic.x][(*T).posic.y + 1] != 'a'))||((*T).poder == 1))){
				(*T).posic.y++;
			}
			(*T).orientacion = 2;
}

void movTanqueAbajo(tanque *T, int nivel){
	if(((*T).posic.x < Niveles[nivel].dim - 1)&&(Niveles[nivel].MatModelo[(*T).posic.x + 1][(*T).posic.y] != 'p')&&(!(colisionTAbajo(*T, Enemigo[0])))&&(!(colisionTAbajo(*T, Enemigo[1])))&&(!(colisionTAbajo(*T, Enemigo[2])))&&(!(colisionTAbajo(*T, Enemigo[3])))&&(!(colisionTAbajo(*T, Jugador)))&&(((Niveles[nivel].MatModelo[(*T).posic.x + 1][(*T).posic.y] != 'a'))||((*T).poder == 1))){
				(*T).posic.x++;
			}
			(*T).orientacion = 3;
}

void movTanqueIzquierda(tanque *T, int nivel){
	if(((*T).posic.y > 0)&&(Niveles[nivel].MatModelo[(*T).posic.x][(*T).posic.y - 1] != 'p')&&(!(colisionTIzquierda(*T, Enemigo[0])))&&(!(colisionTIzquierda(*T, Enemigo[1])))&&(!(colisionTIzquierda(*T, Enemigo[2])))&&(!(colisionTIzquierda(*T, Enemigo[3])))&&(!(colisionTIzquierda(*T, Jugador)))&&(((Niveles[nivel].MatModelo[(*T).posic.x][(*T).posic.y - 1] != 'a'))||((*T).poder == 1))){
				(*T).posic.y--;
			}
			(*T).orientacion = 4;
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


