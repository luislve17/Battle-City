/*
NOTAS:
-fgetc(): mueve el puntero una ubicación siguiente y recién retorna su valor
-Los saltos de linea (ENTER) se leen.
*/

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "InputX.h"

int mygetch(){
	struct termios oldt, newt;
	int ch;

	tcgetattr( STDIN_FILENO, &oldt );

	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );

	tcsetattr( STDIN_FILENO, TCSANOW, &newt );

	ch = getchar();

	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );

	return ch;
}

char getKeyInput(){
	/*
	Espera la entrada de una tecla de direccion por hardware y
	retorna su valor en codigo ascii (A,B,C o D);
	*/
	char ch;
	ch = mygetch();//Recepciona el caracter
	if(ch == '\033'){//Si fue '\033', se espera que se haya presionado una flecha de direccion
		mygetch();//Ignora el '['
		ch = mygetch();//Almacena la letra en cuestión
		return ch;
	}
	else{
		return ch;
	}
	
}
