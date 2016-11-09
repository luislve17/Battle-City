#include <stdio.h>
#include <stdlib.h>
#include "NivelesX.h"

/*
j = jugador
p = pared
a = agua
c = cesped
v = vacio
*/
void cargarNiveles(){
	totalNiveles = 3;//Variable que dicta la cantidad de niveles existentes
	Niveles = (Nivel*)calloc(totalNiveles, sizeof(Nivel));
	
	//Separamos memoria para las contraseñas a los niveles:
	int j;
	for(j = 0; j < totalNiveles; j++){
		Niveles[j].idClave = (char*)calloc(16,sizeof(char));
	}	
	
	//Nivel 0:
	Niveles[0].MatModelo = (char**)calloc(5,sizeof(char*));
	int i;
	for(i = 0; i < 5; i++){
		Niveles[0].MatModelo[i] = (char*)calloc(5,sizeof(char));
	}
	
	Niveles[0].MatModelo[0][0] = 'p';
	Niveles[0].MatModelo[0][1] = 'p';
	Niveles[0].MatModelo[0][2] = 'v';
	Niveles[0].MatModelo[0][3] = 'p';
	Niveles[0].MatModelo[0][4] = 'p';
	
	Niveles[0].MatModelo[1][0] = 'p';
	Niveles[0].MatModelo[1][1] = 'v';
	Niveles[0].MatModelo[1][2] = 'v';
	Niveles[0].MatModelo[1][3] = 'v';
	Niveles[0].MatModelo[1][4] = 'p';
	
	Niveles[0].MatModelo[2][0] = 'p';
	Niveles[0].MatModelo[2][1] = 'v';
	Niveles[0].MatModelo[2][2] = 's';
	Niveles[0].MatModelo[2][3] = 'v';
	Niveles[0].MatModelo[2][4] = 'p';
	
	Niveles[0].MatModelo[3][0] = 'p';
	Niveles[0].MatModelo[3][1] = 'c';
	Niveles[0].MatModelo[3][2] = 'c';
	Niveles[0].MatModelo[3][3] = 'c';
	Niveles[0].MatModelo[3][4] = 'p';
	
	Niveles[0].MatModelo[4][0] = 'p';
	Niveles[0].MatModelo[4][1] = 'p';
	Niveles[0].MatModelo[4][2] = 'p';
	Niveles[0].MatModelo[4][3] = 'p';
	Niveles[0].MatModelo[4][4] = 'p';
	
	Niveles[0].dim = 5;
	Niveles[0].jug_inic = genCoord(0,2);
	Niveles[0].spawns[0] = genCoord(2,2);
	Niveles[0].spawns[1] = genCoord(-1,-1);
	Niveles[0].spawns[2] = genCoord(-1,-1);
	
	Niveles[0].idClave[0] = 'l';
	Niveles[0].idClave[1] = 'v';
	Niveles[0].idClave[2] = 'l';
	Niveles[0].idClave[3] = '0';
	Niveles[0].idClave[4] = '\0';
	Niveles[0].idClave[5] = '\0';
	Niveles[0].idClave[6] = '\0';
	Niveles[0].idClave[7] = '\0';
	Niveles[0].idClave[8] = '\0';
	Niveles[0].idClave[9] = '\0';
	Niveles[0].idClave[10] = '\0';
	Niveles[0].idClave[11] = '\0';
	Niveles[0].idClave[12] = '\0';
	Niveles[0].idClave[13] = '\0';
	Niveles[0].idClave[14] = '\0';
	Niveles[0].idClave[15] = '\0';
		
	//Nivel 1:
	
	Niveles[1].MatModelo = (char**)calloc(10,sizeof(char*));
	
	for(i = 0; i < 10; i++){
		Niveles[1].MatModelo[i] = (char*)calloc(10,sizeof(char));
	}
	
	Niveles[1].MatModelo[0][0] = 'p';
	Niveles[1].MatModelo[0][1] = 'p';
	Niveles[1].MatModelo[0][2] = 'p';
	Niveles[1].MatModelo[0][3] = 'p';
	Niveles[1].MatModelo[0][4] = 'p';
	Niveles[1].MatModelo[0][5] = 'p';
	Niveles[1].MatModelo[0][6] = 'p';
	Niveles[1].MatModelo[0][7] = 'p';
	Niveles[1].MatModelo[0][8] = 'p';
	Niveles[1].MatModelo[0][9] = 'p';
	
	Niveles[1].MatModelo[1][0] = 'p';
	Niveles[1].MatModelo[1][1] = 'v';
	Niveles[1].MatModelo[1][2] = 'v';
	Niveles[1].MatModelo[1][3] = 'v';
	Niveles[1].MatModelo[1][4] = 'v';
	Niveles[1].MatModelo[1][5] = 'v';
	Niveles[1].MatModelo[1][6] = 'v';
	Niveles[1].MatModelo[1][7] = 'v';
	Niveles[1].MatModelo[1][8] = 'v';
	Niveles[1].MatModelo[1][9] = 'p';
	
	Niveles[1].MatModelo[2][0] = 'p';
	Niveles[1].MatModelo[2][1] = 'c';
	Niveles[1].MatModelo[2][2] = 'c';
	Niveles[1].MatModelo[2][3] = 'v';
	Niveles[1].MatModelo[2][4] = 'v';
	Niveles[1].MatModelo[2][5] = 'v';
	Niveles[1].MatModelo[2][6] = 'v';
	Niveles[1].MatModelo[2][7] = 'c';
	Niveles[1].MatModelo[2][8] = 'c';
	Niveles[1].MatModelo[2][9] = 'p';
	
	Niveles[1].MatModelo[3][0] = 'p';
	Niveles[1].MatModelo[3][1] = 'c';
	Niveles[1].MatModelo[3][2] = 'v';
	Niveles[1].MatModelo[3][3] = 'v';
	Niveles[1].MatModelo[3][4] = 'v';
	Niveles[1].MatModelo[3][5] = 'v';
	Niveles[1].MatModelo[3][6] = 'v';
	Niveles[1].MatModelo[3][7] = 'v';
	Niveles[1].MatModelo[3][8] = 'c';
	Niveles[1].MatModelo[3][9] = 'p';
	
	Niveles[1].MatModelo[4][0] = 'p';
	Niveles[1].MatModelo[4][1] = 'v';
	Niveles[1].MatModelo[4][2] = 'v';
	Niveles[1].MatModelo[4][3] = 'v';
	Niveles[1].MatModelo[4][4] = 'c';
	Niveles[1].MatModelo[4][5] = 'c';
	Niveles[1].MatModelo[4][6] = 'v';
	Niveles[1].MatModelo[4][7] = 'v';
	Niveles[1].MatModelo[4][8] = 'v';
	Niveles[1].MatModelo[4][9] = 'p';
	
	Niveles[1].MatModelo[5][0] = 'p';
	Niveles[1].MatModelo[5][1] = 'v';
	Niveles[1].MatModelo[5][2] = 'v';
	Niveles[1].MatModelo[5][3] = 'c';
	Niveles[1].MatModelo[5][4] = 'v';
	Niveles[1].MatModelo[5][5] = 'v';
	Niveles[1].MatModelo[5][6] = 'c';
	Niveles[1].MatModelo[5][7] = 'v';
	Niveles[1].MatModelo[5][8] = 'v';
	Niveles[1].MatModelo[5][9] = 'p';

	Niveles[1].MatModelo[6][0] = 'p';
	Niveles[1].MatModelo[6][1] = 'a';
	Niveles[1].MatModelo[6][2] = 'a';
	Niveles[1].MatModelo[6][3] = 'p';
	Niveles[1].MatModelo[6][4] = 'v';
	Niveles[1].MatModelo[6][5] = 'v';
	Niveles[1].MatModelo[6][6] = 'p';
	Niveles[1].MatModelo[6][7] = 'a';
	Niveles[1].MatModelo[6][8] = 'a';
	Niveles[1].MatModelo[6][9] = 'p';

	Niveles[1].MatModelo[7][0] = 'p';
	Niveles[1].MatModelo[7][1] = 'a';
	Niveles[1].MatModelo[7][2] = 'a';
	Niveles[1].MatModelo[7][3] = 'p';
	Niveles[1].MatModelo[7][4] = 'v';
	Niveles[1].MatModelo[7][5] = 's';
	Niveles[1].MatModelo[7][6] = 'p';
	Niveles[1].MatModelo[7][7] = 'a';
	Niveles[1].MatModelo[7][8] = 'a';
	Niveles[1].MatModelo[7][9] = 'p';
	
	Niveles[1].MatModelo[8][0] = 'p';
	Niveles[1].MatModelo[8][1] = 'v';
	Niveles[1].MatModelo[8][2] = 'v';
	Niveles[1].MatModelo[8][3] = 'v';
	Niveles[1].MatModelo[8][4] = 'v';
	Niveles[1].MatModelo[8][5] = 'v';
	Niveles[1].MatModelo[8][6] = 'v';
	Niveles[1].MatModelo[8][7] = 'v';
	Niveles[1].MatModelo[8][8] = 'v';
	Niveles[1].MatModelo[8][9] = 'p';
	
	Niveles[1].MatModelo[9][0] = 'p';
	Niveles[1].MatModelo[9][1] = 'p';
	Niveles[1].MatModelo[9][2] = 'p';
	Niveles[1].MatModelo[9][3] = 'p';
	Niveles[1].MatModelo[9][4] = 'p';
	Niveles[1].MatModelo[9][5] = 'p';
	Niveles[1].MatModelo[9][6] = 'p';
	Niveles[1].MatModelo[9][7] = 'p';
	Niveles[1].MatModelo[9][8] = 'p';
	Niveles[1].MatModelo[9][9] = 'p';
	
	Niveles[1].dim = 10;
	Niveles[1].jug_inic.x= 5;
	Niveles[1].jug_inic.y = 5;
	Niveles[1].spawns[0] = genCoord(7,5);
	Niveles[1].spawns[1] = genCoord(-1,-1);
	Niveles[1].spawns[2] = genCoord(-1,-1);
	
	Niveles[1].idClave[0] = 'e';
	Niveles[1].idClave[1] = 'z';
	Niveles[1].idClave[2] = '_';
	Niveles[1].idClave[3] = 'j';
	Niveles[1].idClave[4] = 'c';
	Niveles[1].idClave[5] = '_';
	Niveles[1].idClave[6] = 'i';
	Niveles[1].idClave[7] = 'n';
	Niveles[1].idClave[8] = 'v';
	Niveles[1].idClave[9] = 'o';
	Niveles[1].idClave[10] = 'k';
	Niveles[1].idClave[11] = 'e';
	Niveles[1].idClave[12] = 'r';
	Niveles[1].idClave[13] = '\0';
	Niveles[1].idClave[14] = '\0';
	Niveles[1].idClave[15] = '\0';
	
	//Nivel 2
	
	Niveles[2].MatModelo = (char**)calloc(10,sizeof(char*));
	
	for(i = 0; i < 10; i++){
		Niveles[2].MatModelo[i] = (char*)calloc(10,sizeof(char));
	}
	
	Niveles[2].MatModelo[0][0] = 'a';
	Niveles[2].MatModelo[0][1] = 'a';
	Niveles[2].MatModelo[0][2] = 'a';
	Niveles[2].MatModelo[0][3] = 'a';
	Niveles[2].MatModelo[0][4] = 'a';
	Niveles[2].MatModelo[0][5] = 'a';
	Niveles[2].MatModelo[0][6] = 'a';
	Niveles[2].MatModelo[0][7] = 'a';
	Niveles[2].MatModelo[0][8] = 'a';
	Niveles[2].MatModelo[0][9] = 'a';
	
	Niveles[2].MatModelo[1][0] = 'v';
	Niveles[2].MatModelo[1][1] = 'v';
	Niveles[2].MatModelo[1][2] = 'v';
	Niveles[2].MatModelo[1][3] = 'v';
	Niveles[2].MatModelo[1][4] = 'v';
	Niveles[2].MatModelo[1][5] = 'v';
	Niveles[2].MatModelo[1][6] = 'v';
	Niveles[2].MatModelo[1][7] = 'v';
	Niveles[2].MatModelo[1][8] = 'v';
	Niveles[2].MatModelo[1][9] = 'v';
	
	Niveles[2].MatModelo[2][0] = 'v';
	Niveles[2].MatModelo[2][1] = 'v';
	Niveles[2].MatModelo[2][2] = 'v';
	Niveles[2].MatModelo[2][3] = 'v';
	Niveles[2].MatModelo[2][4] = 'c';
	Niveles[2].MatModelo[2][5] = 'c';
	Niveles[2].MatModelo[2][6] = 'v';
	Niveles[2].MatModelo[2][7] = 'v';
	Niveles[2].MatModelo[2][8] = 'v';
	Niveles[2].MatModelo[2][9] = 'v';
	
	Niveles[2].MatModelo[3][0] = 'v';
	Niveles[2].MatModelo[3][1] = 'v';
	Niveles[2].MatModelo[3][2] = 'v';
	Niveles[2].MatModelo[3][3] = 'v';
	Niveles[2].MatModelo[3][4] = 'p';
	Niveles[2].MatModelo[3][5] = 'p';
	Niveles[2].MatModelo[3][6] = 'v';
	Niveles[2].MatModelo[3][7] = 'v';
	Niveles[2].MatModelo[3][8] = 'v';
	Niveles[2].MatModelo[3][9] = 'v';
	
	Niveles[2].MatModelo[4][0] = 'v';
	Niveles[2].MatModelo[4][1] = 'v';
	Niveles[2].MatModelo[4][2] = 'v';
	Niveles[2].MatModelo[4][3] = 'v';
	Niveles[2].MatModelo[4][4] = 'v';
	Niveles[2].MatModelo[4][5] = 'v';
	Niveles[2].MatModelo[4][6] = 'v';
	Niveles[2].MatModelo[4][7] = 'v';
	Niveles[2].MatModelo[4][8] = 'v';
	Niveles[2].MatModelo[4][9] = 'v';
	
	Niveles[2].MatModelo[5][0] = 'v';
	Niveles[2].MatModelo[5][1] = 'v';
	Niveles[2].MatModelo[5][2] = 'v';
	Niveles[2].MatModelo[5][3] = 'v';
	Niveles[2].MatModelo[5][4] = 'p';
	Niveles[2].MatModelo[5][5] = 'p';
	Niveles[2].MatModelo[5][6] = 'v';
	Niveles[2].MatModelo[5][7] = 'v';
	Niveles[2].MatModelo[5][8] = 'v';
	Niveles[2].MatModelo[5][9] = 'v';
	
	Niveles[2].MatModelo[6][0] = 'v';
	Niveles[2].MatModelo[6][1] = 'v';
	Niveles[2].MatModelo[6][2] = 'v';
	Niveles[2].MatModelo[6][3] = 'v';
	Niveles[2].MatModelo[6][4] = 'c';
	Niveles[2].MatModelo[6][5] = 'c';
	Niveles[2].MatModelo[6][6] = 'v';
	Niveles[2].MatModelo[6][7] = 'v';
	Niveles[2].MatModelo[6][8] = 'v';
	Niveles[2].MatModelo[6][9] = 'v';

	Niveles[2].MatModelo[7][0] = 'p';
	Niveles[2].MatModelo[7][1] = 'a';
	Niveles[2].MatModelo[7][2] = 'a';
	Niveles[2].MatModelo[7][3] = 'a';
	Niveles[2].MatModelo[7][4] = 'a';
	Niveles[2].MatModelo[7][5] = 'a';
	Niveles[2].MatModelo[7][6] = 'a';
	Niveles[2].MatModelo[7][7] = 'a';
	Niveles[2].MatModelo[7][8] = 'a';
	Niveles[2].MatModelo[7][9] = 'p';
	
	Niveles[2].MatModelo[8][0] = 'p';
	Niveles[2].MatModelo[8][1] = 'a';
	Niveles[2].MatModelo[8][2] = 'a';
	Niveles[2].MatModelo[8][3] = 'a';
	Niveles[2].MatModelo[8][4] = 'a';
	Niveles[2].MatModelo[8][5] = 'a';
	Niveles[2].MatModelo[8][6] = 'a';
	Niveles[2].MatModelo[8][7] = 'a';
	Niveles[2].MatModelo[8][8] = 'a';
	Niveles[2].MatModelo[8][9] = 'p';
	
	Niveles[2].MatModelo[9][0] = 'p';
	Niveles[2].MatModelo[9][1] = 'p';
	Niveles[2].MatModelo[9][2] = 'p';
	Niveles[2].MatModelo[9][3] = 'p';
	Niveles[2].MatModelo[9][4] = 'p';
	Niveles[2].MatModelo[9][5] = 'p';
	Niveles[2].MatModelo[9][6] = 'p';
	Niveles[2].MatModelo[9][7] = 'p';
	Niveles[2].MatModelo[9][8] = 'p';
	Niveles[2].MatModelo[9][9] = 'p';
	
	Niveles[2].dim = 10;
	Niveles[2].jug_inic.x = 2;
	Niveles[2].jug_inic.y = 1;
	
	Niveles[2].idClave[0] = 'n';
	Niveles[2].idClave[1] = 'o';
	Niveles[2].idClave[2] = '_';
	Niveles[2].idClave[3] = 'm';
	Niveles[2].idClave[4] = 'e';
	Niveles[2].idClave[5] = '_';
	Niveles[2].idClave[6] = 'v';
	Niveles[2].idClave[7] = 'a';
	Niveles[2].idClave[8] = 'l';
	Niveles[2].idClave[9] = 'e';
	Niveles[2].idClave[10] = '\0';
	Niveles[2].idClave[11] = '\0';
	Niveles[2].idClave[12] = '\0';
	Niveles[2].idClave[13] = '\0';
	Niveles[2].idClave[14] = '\0';
	Niveles[2].idClave[15] = '\0';		
}

int sonEquiv(char* p1, char* p2){
	int i, j;
	
	for(i = 0; i < 16; i++){
		if(p1[i] != p2[i]){
			return 0;
		}
	}
	return 1;
}

int buscarNivelxClave(char* claveIngresada){
	int i;
	for(i = 0; i < totalNiveles; i++){
		if(sonEquiv((char*)Niveles[i].idClave, claveIngresada)){
			return i;
		}
	}
	return -1;
}


coordenada genCoord(int a, int b){
	coordenada result;
	result.x = a;
	result.y = b;
	return result;
}

void descargarNiveles(){
	int i, j;
	for(i = 0; i < totalNiveles; i++){
		//Liberamos la matriz del nivel 'i'
		for(j = 0; j < Niveles[i].dim; j++){
			free(Niveles[i].MatModelo[j]);
		}
		free(Niveles[i].MatModelo);
		
		//Liberamos su String idClave
		free(Niveles[i].idClave);
	}
	free(Niveles);
}
