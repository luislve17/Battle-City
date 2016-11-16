#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "MotorX.h"
#include "InputX.h"
#include "AnimX.h"
#include "NivelesX.h"
#include "GraphX.h"
#include "AlgoritmoX.h"

#define NORM  "\x1B[0m"
#define ROJO  "\x1B[31m"
#define VERD  "\x1B[32m"
#define AMAR  "\x1B[33m"
#define AZUL  "\x1B[34m"
#define MAGN  "\x1B[35m"
#define CYAN  "\x1B[36m"
#define BLNC  "\x1B[37m"
#define BOLD "\033[1m"

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

char** actualMatNivel(char** MatrizNivel, char** MatModelo, int dim_modelo){
	int i, j;
	char ch;
	for(i = 0; i < dim_modelo; i++){
		for(j = 0; j < dim_modelo; j++){
			ch = MatModelo[i][j];
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
		else if(Enemigo[i].vida == 0){
			Enemigo[i].posic = genCoord(-1,-1);
		}
	}
	for(i = 0; i < 8; i++){
		if(Bala[i].posic.x != -1){
			MatEntidades = setProyectil(Bala[i], MatEntidades);
		}
	}
	
	if(baseActual.posic.x != -1){
		MatEntidades[3*baseActual.posic.x + 1][3*baseActual.posic.y + 1] = '*';
	}
	return MatEntidades;
}

//<Funciones de colisión>
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
	if((t1.posic.x + 1 == t2.posic.x)&&(t1.posic.y == t2.posic.y)){
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

bool colisionPArriba(proyectil p, tanque T){
	if((p.posic.x - 1 == T.posic.x)&&(p.posic.y == T.posic.y)){
		return true;
	}
	return false;
}

bool colisionPDerecha(proyectil p, tanque T){
	if((p.posic.x == T.posic.x)&&(p.posic.y + 1 == T.posic.y)){
		return true;
	}
	return false;
}

bool colisionPAbajo(proyectil p, tanque T){
	if((p.posic.x + 1 == T.posic.x)&&(p.posic.y == T.posic.y)){
		return true;
	}
	return false;
}

bool colisionPIzquierda(proyectil p, tanque T){
	if((p.posic.x == T.posic.x)&&(p.posic.y - 1 == T.posic.y)){
		return true;
	}
	return false;
}


bool colisionBArriba(proyectil p){
	if((p.posic.x - 1 == baseActual.posic.x)&&((p.posic.y == baseActual.posic.y))){
		return true;
	}
	return false;
}

bool colisionBDerecha(proyectil p){
	if((p.posic.x == baseActual.posic.x)&&((p.posic.y + 1 == baseActual.posic.y))){
		return true;
	}
	return false;
}

bool colisionBAbajo(proyectil p){
	if((p.posic.x + 1 == baseActual.posic.x)&&((p.posic.y == baseActual.posic.y))){
		return true;
	}
	return false;
}

bool colisionBIzquierda(proyectil p){
	if((p.posic.x == baseActual.posic.x)&&((p.posic.y - 1== baseActual.posic.y))){
		return true;
	}
	return false;
}
//</Funciones de colisión>

void printVida(){
	int i;
	printf("Vida [");
	for(i = 0; i < Jugador.vida; i++){
		printf(BOLD ROJO " \u2665 " NORM);
	}
	while(i < 4){
		printf(BOLD " \u2661 " NORM);
		i++;
	}
	printf("]\n");
}

void printPoder(){
	printf("PODER: ");
	switch(Jugador.poder){
		case 0:
			printf("NINGUNO");
			break;
		case 1:
			printf("FLOTAR");
			break;
	}
	printf("\n");
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

void printPantallaNivel(int nivel){
	int cont = 0;
	impFotograma(28 + nivel);//imprime la pantalla de cada nivel
	while(cont < 70){
		minisleep();
		cont++;
	}
}

void printNivel(char** MatrizNivel, char** MatrizEntidades, int** resistenciaPared, int dim_Matriz){
	int i, j;
	char aux1, aux2;
	printVida();
	printPoder();
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
					int aux3 = resistenciaPared[i/3][j/3];
					switch(aux3){
						case 0:
							printf(ROJO " %c " NORM,aux1);
							break;
						case -1:
							printf(BOLD ROJO " %c " NORM,aux1);
							break;
						case -2:
							printf(BOLD MAGN " %c " NORM, aux1);
							break;
					}
				}
				else{
					printf(NORM " %c " NORM, aux1);
				}
			}
			else{
				if(((i >= 3*Jugador.posic.x)&&(i <= 3*Jugador.posic.x + 2))&&(j >= 3*Jugador.posic.y)&&(j <= 3*Jugador.posic.y + 2)){//Jugador
					printf(BOLD AZUL " %c " NORM, aux2);
				}
				else if(aux2 == '*'){
					printf(BOLD " \u2390 " NORM);
				}
				else{
					printf(BOLD " %c " NORM, aux2);
				}
			}
		}
		printf("\n");
	}
}

int ejecutarEnNivel(int nivel){
	printPantallaNivel(nivel);
	limpOut(22);

	char ** MatNv, ** MatEnti;
	int enemigosEnPantalla = 0;
	int balasEnPantalla = 0;
	
	time_t t;
	srand((unsigned)time(&t));
	
	MatNv = defMatNivel(Niveles[nivel].MatModelo, Niveles[nivel].dim);
	MatEnti = inicMatEntidades(Niveles[nivel].dim);
	
	Jugador.posic = Niveles[nivel].jug_inic;
	Jugador.orientacion = rand()%4 + 1; //Orientacion aleatoria
	Jugador.vida = 4;
	
	baseActual.posic = Niveles[nivel].base_nivel.posic; 
	baseActual.vida = 1;
	
	MatEnti = actualMatEntidades(MatEnti, 3*Niveles[nivel].dim);
	char key;
	
	graph* G = getMapGraph(Niveles + nivel); // Niveles + nivel = &(Niveles[nivel]) FYI
	setStartNode(G, &Jugador.posic);
	ticks = 0;//Inicializamos los ticks
	resetEnemigos();
	resetBalas();
	while(1){
	
		if((Jugador.vida < 0)||(baseActual.vida <= 0)){//Derrota
			gameOver();
			return 0;
		}
		
		if((enemigosEnPantalla == 4)&&(enemigosVencidos())){
			return 1;
		}
		
		printNivel(MatNv, MatEnti, Niveles[nivel].resistenciaPared, 3*(Niveles[nivel].dim));
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
		else if(key == ' '){
			if(balasEnPantalla < 8){
				addBala(Jugador.posic,Jugador.orientacion);
			}
		}
		else if(key == '\n'){//Nivel finalizado
			break;
		}
		else if(key == 'q'){//Personaje derrotado o equivalente
			game_over = true;
			return 0;
		}
		movBalas(nivel);
		MatNv = actualMatNivel(MatNv, Niveles[nivel].MatModelo, Niveles[nivel].dim);
		MatEnti = actualMatEntidades(MatEnti, 3*(Niveles[nivel].dim));
		
		ticks = (ticks + 1)%30;//Los ticks del juego irán del 0 al 29 por cada movimiento y se reiniciará
		
		if((ticks == 0)&&(enemigosEnPantalla < 4)&&(Niveles[nivel].cant_spawns > 0)){
			int spawn_seleccionado = rand()%(Niveles[nivel].cant_spawns);
			addEnemigo(Niveles[nivel].spawns[spawn_seleccionado]);
			enemigosEnPantalla++;
		}
		MatNv = actualMatNivel(MatNv, Niveles[nivel].MatModelo, Niveles[nivel].dim);
		MatEnti = actualMatEntidades(MatEnti, 3*(Niveles[nivel].dim));
		// ###########################################################
		// Movimiento del enemigo
		if(ticks%2 == 0){
			movBFSEnemigos(G, nivel);
		}
		else{
			movRandomEnemigos(nivel);
		}
		// ###########################################################
		
		MatNv = actualMatNivel(MatNv, Niveles[nivel].MatModelo, Niveles[nivel].dim);
		MatEnti = actualMatEntidades(MatEnti, 3*(Niveles[nivel].dim));
		limpOut(3*(Niveles[nivel].dim) + 3);

		//De momento solo se actualizan las entidades, pero el terreno también deberá
		MatNv = actualMatNivel(MatNv, Niveles[nivel].MatModelo, Niveles[nivel].dim);
		MatEnti = actualMatEntidades(MatEnti, 3*(Niveles[nivel].dim));
		
		resetGraph(G, Niveles + nivel);
		setStartNode(G, &Jugador.posic);
		BFS(G);
		
	}
	resetEnemigos();
	deleteGraph(G);
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
		Enemigo[i].agresividad = rand()%20 + 10;// rango de ferocidad 10%-30%
		return true;//Generacion de enemigo exitosa
	}
	return false;//Generacion de enemigo no exitosa
}

bool enemigosVencidos(){
	int i;
	for(i = 0; i < 4; i++){
		if(Enemigo[i].vida > 0){
			return false;
		}
	}
	return true;
}

void resetBalas(){
	int i;
	for(i = 0; i < 8; i++){
		Bala[i].posic = genCoord(-1, -1);
	}
}

bool addBala(coordenada pos_inic, int dir){
	int i = 0;
	while((i < 8)&&(Bala[i].posic.x != -1)){
		i++;
	}
	
	if(Bala[i].posic.x == -1){
		Bala[i].posic = pos_inic;
		Bala[i].orientacion = dir;
		return true;
	}
	return false;
}

void movRandomEnemigos(int nivel){
	//Es necesario actualizar la matriz cada vez que se mueve un tanque
	int i;
	for(i = 0; i < 4; i++){
		if(Enemigo[i].posic.x != -1){
			movRandom(&(Enemigo[i]), nivel);
		}
	}
}

void movRandom(tanque *T, int nivel){
	time_t t;
	srand((unsigned)time(&t));
	
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

void movBFSEnemigos(graph* G, int nivel)
{
	int i;
	for(i = 0; i < 4; i++){
		if(Enemigo[i].posic.x != -1){
			movBFS(G, &(Enemigo[i]), nivel);
		}
	}
}

void movBFS(graph* G, tanque *T, int nivel)
{
	int direccion = G->matrix[T->posic.x][T->posic.y].d;
	
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
	if(rand()%101 < T->agresividad )
	{
		addBala(T->posic, T->orientacion);
	}
}

void movBalas(int nivel){
	int i;
	for(i = 0; i < 8; i++){
		if((Bala[i].posic.x == 0 && Bala[i].orientacion == 1) || (Bala[i].posic.y == 0 && Bala[i].orientacion == 4) || (Bala[i].posic.x == Niveles[nivel].dim - 1 && Bala[i].orientacion == 3) || (Bala[i].posic.y == Niveles[nivel].dim - 1 && Bala[i].orientacion == 2))
		{
			Bala[i].posic = genCoord(-1, -1);
			continue;
		}
		if(Bala[i].posic.x != -1) {
			movProyectil(&(Bala[i]), nivel);
		}
	}
}

void movProyectil(proyectil *p, int nivel){
	switch((*p).orientacion){
		case 1:
			movProyArriba(p, nivel);
			break;
		case 2:
			movProyDerecha(p, nivel);
			break;
		case 3:
			movProyAbajo(p, nivel);
			break;
		case 4:
			movProyIzquierda(p, nivel);
			break;
	}
}

//<Estados del juego>
void inicJuego(int nivel_inic){
	game_over = 0;//Se inicializa el juego
	int nivel = nivel_inic;//Nivel inicial

	while((!game_over)&&(nivel < totalNiveles)){//Se irán acumulando los niveles sumando al game_over
		limpOut(3*(Niveles[nivel].dim) + 3);
		nivel += ejecutarEnNivel(nivel);
	}
}
void gameOver(){
	impFotograma(27);
	int delay = 0;
	while(delay != 100){
		minisleep();
		delay++;
	}
	limpOut(22);
	game_over = true;
}
//</Estados del juego>

//<funciones de movimiento-colision>
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

void movProyArriba(proyectil *p, int nivel){
	if(((*p).posic.x > 0)&&(Niveles[nivel].MatModelo[(*p).posic.x - 1][(*p).posic.y] != 'p')&&(!colisionPArriba(*p, Enemigo[0]))&&(!colisionPArriba(*p, Enemigo[1]))&&(!colisionPArriba(*p, Enemigo[2]))&&(!colisionPArriba(*p, Enemigo[3]))&&(!colisionPArriba(*p, Jugador))&&(!colisionBArriba(*p))){
		(*p).posic.x--;
	}
	else{
		if(Niveles[nivel].MatModelo[(*p).posic.x - 1][(*p).posic.y] == 'p'){
			Niveles[nivel].resistenciaPared[(*p).posic.x - 1][(*p).posic.y]--;
			
			if(Niveles[nivel].resistenciaPared[(*p).posic.x - 1][(*p).posic.y] == -3)
				Niveles[nivel].MatModelo[(*p).posic.x - 1][(*p).posic.y] = 'v';
		}
		else if(colisionPArriba(*p, Enemigo[0])){
			Enemigo[0].vida--;
		}
		else if(colisionPArriba(*p, Enemigo[1])){
			Enemigo[1].vida--;
		}
		else if(colisionPArriba(*p, Enemigo[2])){
			Enemigo[2].vida--;
		}
		else if(colisionPArriba(*p, Enemigo[3])){
			Enemigo[3].vida--;
		}
		else if(colisionPArriba(*p, Jugador)){
			Jugador.vida--;
		}
		else if(colisionBArriba(*p)){
			baseActual.vida--;
		}
		(*p).posic = genCoord(-1,-1);
	}
}

void movProyDerecha(proyectil *p, int nivel){
	if(((*p).posic.y < Niveles[nivel].dim - 1)&&(Niveles[nivel].MatModelo[(*p).posic.x][(*p).posic.y + 1] != 'p')&&(!colisionPDerecha(*p, Enemigo[0]))&&(!colisionPDerecha(*p, Enemigo[1]))&&(!colisionPDerecha(*p, Enemigo[2]))&&(!colisionPDerecha(*p, Enemigo[3]))&&(!colisionPDerecha(*p, Jugador))&&(!colisionBDerecha(*p))){
		(*p).posic.y++;
	}
	else{ 
		if(Niveles[nivel].MatModelo[(*p).posic.x][(*p).posic.y + 1] == 'p'){
			Niveles[nivel].resistenciaPared[(*p).posic.x][(*p).posic.y + 1]--;
			
			if(Niveles[nivel].resistenciaPared[(*p).posic.x][(*p).posic.y + 1] == -3)
				Niveles[nivel].MatModelo[(*p).posic.x][(*p).posic.y + 1] = 'v';
		}
		else if(colisionPDerecha(*p, Enemigo[0])){
			Enemigo[0].vida--;
		}
		else if(colisionPDerecha(*p, Enemigo[1])){
			Enemigo[1].vida--;
		}
		else if(colisionPDerecha(*p, Enemigo[2])){
			Enemigo[2].vida--;
		}
		else if(colisionPDerecha(*p, Enemigo[3])){
			Enemigo[3].vida--;
		}
		else if(colisionPDerecha(*p, Jugador)){
			Jugador.vida--;
		}
		else if(colisionBDerecha(*p)){
			baseActual.vida--;
		}
		(*p).posic = genCoord(-1,-1);
	}
}

void movProyAbajo(proyectil *p, int nivel){
	if(((*p).posic.x < Niveles[nivel].dim - 1)&&(Niveles[nivel].MatModelo[(*p).posic.x + 1][(*p).posic.y] != 'p')&&(!colisionPAbajo(*p, Enemigo[0]))&&(!colisionPAbajo(*p, Enemigo[1]))&&(!colisionPAbajo(*p, Enemigo[2]))&&(!colisionPAbajo(*p, Enemigo[3]))&&(!colisionPAbajo(*p, Jugador))&&(!colisionBAbajo(*p))){
		(*p).posic.x++;
	}
	else{ 
		if(Niveles[nivel].MatModelo[(*p).posic.x + 1][(*p).posic.y] == 'p'){
			Niveles[nivel].resistenciaPared[(*p).posic.x + 1][(*p).posic.y]--;
			
			if(Niveles[nivel].resistenciaPared[(*p).posic.x + 1][(*p).posic.y] == -3)
				Niveles[nivel].MatModelo[(*p).posic.x + 1][(*p).posic.y] = 'v';
		}
		else if(colisionPAbajo(*p, Enemigo[0])){
			Enemigo[0].vida--;
		}
		else if(colisionPAbajo(*p, Enemigo[1])){
			Enemigo[1].vida--;
		}
		else if(colisionPAbajo(*p, Enemigo[2])){
			Enemigo[2].vida--;
		}
		else if(colisionPAbajo(*p, Enemigo[3])){
			Enemigo[3].vida--;
		}
		else if(colisionPAbajo(*p, Jugador)){
			Jugador.vida--;
		}
		else if(colisionBAbajo(*p)){
			baseActual.vida--;
		}
		(*p).posic = genCoord(-1,-1);
	}
}

void movProyIzquierda(proyectil *p, int nivel){
	if(((*p).posic.y > 0)&&(Niveles[nivel].MatModelo[(*p).posic.x][(*p).posic.y - 1] != 'p')&&(!colisionPIzquierda(*p, Enemigo[0]))&&(!colisionPIzquierda(*p, Enemigo[1]))&&(!colisionPIzquierda(*p, Enemigo[2]))&&(!colisionPIzquierda(*p, Enemigo[3]))&&(!colisionPIzquierda(*p, Jugador))&&(!colisionBIzquierda(*p))){
		(*p).posic.y--;
	}
	else{ 
		if(Niveles[nivel].MatModelo[(*p).posic.x][(*p).posic.y - 1] == 'p'){
			Niveles[nivel].resistenciaPared[(*p).posic.x][(*p).posic.y - 1]--;
			
			if(Niveles[nivel].resistenciaPared[(*p).posic.x][(*p).posic.y - 1] == -3)
				Niveles[nivel].MatModelo[(*p).posic.x][(*p).posic.y - 1] = 'v';
		}
		else if(colisionPIzquierda(*p, Enemigo[0])){
			Enemigo[0].vida--;
		}
		else if(colisionPIzquierda(*p, Enemigo[1])){
			Enemigo[1].vida--;
		}
		else if(colisionPIzquierda(*p, Enemigo[2])){
			Enemigo[2].vida--;
		}
		else if(colisionPIzquierda(*p, Enemigo[3])){
			Enemigo[3].vida--;
		}
		else if(colisionPIzquierda(*p, Jugador)){
			Jugador.vida--;
		}
		else if(colisionBIzquierda(*p)){
			baseActual.vida--;
		}
		(*p).posic = genCoord(-1,-1);
	}
}


//</funciones de movimiento-colision>

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

char** setProyectil(proyectil bala, char** MatrizEntidades){
	switch(bala.orientacion){
		case 1:
			MatrizEntidades[3*bala.posic.x + 1][3*bala.posic.y + 1] = '^';
			break;
		case 2:
			MatrizEntidades[3*bala.posic.x + 1][3*bala.posic.y + 1] = '>';
			break;
		case 3:
			MatrizEntidades[3*bala.posic.x + 1][3*bala.posic.y + 1] = 'v';
			break;
		case 4:
			MatrizEntidades[3*bala.posic.x + 1][3*bala.posic.y + 1] = '<';
			break;
	}
	return MatrizEntidades;
}
//</funciones visuales en matriz>
