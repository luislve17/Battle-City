#include <stdio.h>
#include <stdlib.h>
#include "NivelesX.h"
#include <string.h>
#include "UtilX.h"

/*
j = jugador
p = pared
a = agua
c = cesped
v = vacio
s = spawn
*/
void cargarNiveles()
{
	totalNiveles = 2;
	Niveles = (Nivel*)calloc(totalNiveles, sizeof(Nivel));
	
	FILE* levelFile;
	levelFile = fopen("./resources/testLevel.txt", "r");
	if(levelFile == NULL)
	{
		printf("Error abriendo el archivo de niveles\n");
	}
	
	int loading = 1; // controla si todavía se puede leer el archivo y cargar un nivel
	char linea[40]; // string que almacenara una linea del archivo
	int dimension;
	int i, j;
	int nivelCargado = 0; // indice del nivel que se esta cargando
	
	//Separamos memoria para las contraseñas a los niveles:
	for(j = 0; j < totalNiveles; j++){
		Niveles[j].idClave = (char*)calloc(16,sizeof(char));
	}
	
	while(loading)
	{
		if(fgets((char*)linea, 40, levelFile) == NULL)
		{
			loading = 0;
			continue;
		}
	
		dimension = strToInt(linea); // dimension del nivel actual
		
		//Separar nivel
		Niveles[nivelCargado].MatModelo = (char**)calloc(dimension,sizeof(char*));
		for(i = 0; i < dimension; i++){
			Niveles[nivelCargado].MatModelo[i] = (char*)calloc(dimension,sizeof(char));
		}	
			
		Niveles[nivelCargado].dim = dimension;
		
		int spawnCount = 0; // contador para el indice del spawn actual
		for(i = 0; i < dimension; i++) // se lee tantas lineas como la dimension
		{
			if(fgets((char*)linea, 40, levelFile) == NULL) // se lee la sgte linea
			{
				loading = 0;
				continue;
			}
			int j;
			for(j = 0; j < dimension; j++) // se lee cada caracter de la linea
			{
				switch(linea[j])
				{
					case 'x':
						Niveles[nivelCargado].MatModelo[i][j] = 'p';
						break;
					case ' ':
						Niveles[nivelCargado].MatModelo[i][j] = 'v';
						break;
					case 'j':
						Niveles[nivelCargado].MatModelo[i][j] = 'v';
						Niveles[nivelCargado].jug_inic = genCoord(i,j);
						break;
					case 'v':
						Niveles[nivelCargado].MatModelo[i][j] = 'c';
						break;
					case '-':
						Niveles[nivelCargado].MatModelo[i][j] = 'a';
						break;
					case 'S':
						Niveles[nivelCargado].MatModelo[i][j] = 's';
						Niveles[nivelCargado].spawns[spawnCount++] = genCoord(i,j);
						break;
					
					default:
						printf("Formato inválido en el nivel, mapa %d, linea %d, caracter %d\n", nivelCargado, i, j);
						return;
						break;
				}
			}
			
			
			for(j = spawnCount; j < 3; j++) // configura las coordenadas de los spawns no usados
			{
				Niveles[nivelCargado].spawns[j] = genCoord(-1,-1);
			}
		}
		Niveles[nivelCargado].cant_spawns = spawnCount;
		nivelCargado++;
	}
	
	
	if(fclose(levelFile))
	{
		printf("Error cerrando el archivo de niveles\n");
	}

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
