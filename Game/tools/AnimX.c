#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "InputX.h"
#include "AnimX.h"
#include "MotorX.h"
#include "NivelesX.h"

void invocMenu(){
	limpOut(256);
	bool quit = false;//Controlador del menu
	int animFlag = 0;//Estado o fotograma inicial de la animación del menú
	char selec;
	impFotograma(1);
	while(!quit){//Menu no circular
		selec = getKeyInput();
		if((selec == 'A')&&(animFlag > 0)){//Mover seleccion hacia arriba
			animFlag--;
			genAnimMenu(animFlag + 1, animFlag);//Animar desplazamiento de cuadro actual (animFlag + 1) a cuadro destino (animFlag)
		}
		if((selec == 'B')&&(animFlag < 2)){//Mover seleccion hacia abajo
			animFlag++;
			genAnimMenu(animFlag - 1, animFlag);//Animar desplazamiento de cuadro actual (animFlag - 1) a cuadro destino (animFlag)
		}
		if(selec == '\n'){//Seleccionar opcion actual
			genAnimMenu(animFlag, animFlag);//Animar seleccion
			if(animFlag == 0){//Si la seleccion corresponde a la primera opcion (opcion 0 JUGAR)
				limpOut(22);//Limpia de pantalla
				cargarNiveles();
				inicJuego(0);
				
				descargarNiveles();
				quit = true;//Al acabar se acaba el proceso total
			}
			if(animFlag == 1){//Si la seleccion corresponde a la segunda opcion (opcion 1 CLAVE)
				cargarNiveles();
				int nivel = menuClave();
				if(nivel >= 0){
					//<Limpia de pantalla>
					int aux = 0;
					while(aux < 13){
						fputs("\033[D\033[D\033[D\033[B",stdout);//Regresamos el puntero de a la base del menu y lo mas proximo a la izquierda
						aux++;
					}
					limpOut(22);
					///Limpia de pantalla>
					inicJuego(nivel);
					
					descargarNiveles();
					quit = true;//Al acabar se acaba el proceso total
				}
			}
			if(animFlag == 2){//Si la seleccion corresponde a la tercera opcion (opcion 2 SALIR)
				limpOut(22);
				quit = true;
			}
		}
	}
}

void limpOut(int backsteps){
	//Funcion que limpia tantas lineas hacia arriba en el output del terminal como backsteps
	while(backsteps != 0){
		fputs("\033[A\033[2K",stdout);
		backsteps--;
	}
	rewind(stdout);
}

void minisleep(){
	//Delay de 0.25 segundos utilizado para realizar las animaciones
	nanosleep((const struct timespec[]){{0, 25000000L}}, NULL);
}

void genAnimMenu(int frameFlag1, int frameFlag2){
	//Funcion generadora de la animacion del menu
	//frameFlag1 = Fotograma inicial de animacion
	//frameFlag2 = Fotograma final de animacion
	//Esto solo como analogía, en realidad para ir a un cuadro en especifico
	//se revisa el valor de las frameFlags y se dispone a animar diferentes
	//fotogramas del menu
	int i;
	if(frameFlag1 != frameFlag2){
	//Si las frameFlags son diferentes, se trata de una animacion de
	//desplazamiento, para pasar de una seleccion a otra
		if((frameFlag1 == 0)&&(frameFlag2 == 1)){//Si se desea animar el desplaz. de la opcion '0' a la '1'
			limpOut(22);
			for(i = 1; i <= 6; i++){//Imprimimos cada fotograma del 1 al 6 con un delay en medio para apreciar la animacion
				impFotograma(i);
				minisleep();
				limpOut(22);
			}
			impFotograma(6);
		}
		else if((frameFlag1 == 1)&&(frameFlag2 == 0)){//Si se desea animar el desplaz. de la opcion '1' a la '0', similarmente
			limpOut(22);
			for(i = 6; i <= 11; i++){
				impFotograma(i);
				minisleep();
				limpOut(22);
			}
			impFotograma(11);
		}
		else if((frameFlag1 == 1)&&(frameFlag2 == 2)){//Similar
			limpOut(22);
			for(i = 14; i <= 19; i++){
				impFotograma(i);
				minisleep();
				limpOut(22);
			}
			impFotograma(19);
		}
		else if((frameFlag1 == 2)&&(frameFlag2 == 1)){//Similar
			limpOut(22);
			for(i = 19; i <= 23; i++){
				impFotograma(i);
				minisleep();
				limpOut(22);
			}
			impFotograma(23);
		}
	}
	else{
	//Si las frameFlags son iguales, se trata de una animacion
	//de seleccion de opcion
		if(frameFlag1 == 0){//Se desea animar la seleccion de la opcion '0' del menu
			limpOut(22);
			impFotograma(12);
			minisleep();
			minisleep();
			limpOut(22);
			impFotograma(1);
		}
		else if(frameFlag1 == 1){//Se desea animar la seleccion de la opcion '1' del menu
			limpOut(22);
			impFotograma(13);
			minisleep();
			minisleep();
			limpOut(22);
			impFotograma(6);
		}
		else if(frameFlag1 == 2){//Se desea animar la seleccion de la opcion '2' del menu
			limpOut(22);
			impFotograma(25);
			minisleep();
			minisleep();
			limpOut(22);
			impFotograma(19);
		}
	}
}

int menuClave(){//Se invoca al menu de claves
	int cont = 0;
	int i, nivel;//Nivel de destino luego de ingresar la clave
	
	char clave[16];//Aqui se almacenará la clave que ingrese el usuario
	for(i = 0; i < 16; i++){
		clave[i] = '\0';
	}
	
	
	limpOut(22);
	impFotograma(26);
	
	//<Posicionamiento del Ibeam>
	while(cont < 13){
		fputs("\033[A",stdout);
		cont++;
	}
	cont = 0;
	while(cont < 20)
	{
		fputs("\033[C",stdout);
		cont++;
	}
	//</Posicionamiento del Ibeam>
	
	cont = 0;
	char ch;
	ch = (char)mygetch(); 
	while(ch != '\n'){
		if((ch != 127)&&(cont < 15)){
			printf("%c " ,ch);
			clave[cont] = ch;
			cont++;
		}
		else if((ch == 127)&&(cont > 0)){
			fputs("\033[D\033[D \033[D",stdout);
			cont--;
			clave[cont] = '\0';
		}
		ch = (char)mygetch();
	}
	nivel = buscarNivelxClave(clave);
	return nivel;
}

void impFotograma(int i){//Recibe el numero de fotograma que se desea imprimir y lo imprime en pantalla
	//Altura de cada frame: 22
	if(i <= 29){//Número máximo de frames
		FILE* fptr = fopen("resources/Menu_principal.txt", "r");
		int cont = 1;
		char ch;
		while(cont < i){//Buscar el frame
			ch = fgetc(fptr);
			while(ch != '?'){
				ch = fgetc(fptr);
			}
			cont++;
		}
		ch = fgetc(fptr);
		while(ch != '?'){
			printf("%c",ch);
			ch = fgetc(fptr);
		}
		fclose(fptr);
	}
}
