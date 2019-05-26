//============================================================================
// Name        : UnTest.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sstream>
#include "Pruebita.h"
#include "EasyBMP.h"
#include "EasyBMP_DataStructures.h"
#include "Tablero.h"
#include "Ficha.h"
#include "ImagenMultiple.h"

using namespace std;
#define X 20
#define Y 20
#define Z 20
#define A 5

int main( ) {
	int dimension_tablero[3] = {X,Y,Z};
	int unaUbicacionEnTablero[3];
	int cantidadDeJugadores = A;
	Tablero *elTableroDeUnTest = new Tablero(dimension_tablero);
	Ficha *fichita;

	// una version pseudo-aleatoria del juego jajaj
	for ( int i = 1; i <= X; i++) {
		for ( int j = 1; j <= Y; j++) {
			for (int jj = 1; jj <= Z; jj++) { // i*i + 2*j + jj*j*i
				if ( -(i-X/2)*(i-X/2)/X-(j-Y/2)*(j-Y/2)/Y +Z > jj ) {
				fichita = new Ficha(( i*i+j+jj*j) % A + 1); //el +1 es para que los jugadores estén desde 1 hasta A;
				unaUbicacionEnTablero[0] = i;
				unaUbicacionEnTablero[1] = j;
				unaUbicacionEnTablero[2] = jj;
				// fichita->color = circle.GetColor() //habría que usar esta funcion si se quiere llenar las fichas en tiempo de ejecución.
				elTableroDeUnTest->guardarFicha(fichita, unaUbicacionEnTablero);
				}
			}
		}
	}

	/*---- Version para leer las fichas de los jugadores ----*/
	ImagenMultiple *circle = new ImagenMultiple();
	circle->cargarImagenes("/home/hernan/workspace/UnTest/Imagenes/Load/",
						   "circle",
						   cantidadDeJugadores,	// la cantidad de jugadores es la cantidad de imágenes a cargar.
						   ".bmp");

	/* ==== 				========					====*/

	/*----Version para obtener imágenes de las plantas---- */

		ImagenMultiple *outPutPiso = new ImagenMultiple();

		outPutPiso->generarVistaEnNivelesXY(circle, elTableroDeUnTest);

		outPutPiso->guardarImagenes("/home/hernan/workspace/UnTest/Imagenes/Load/",
								   "outputPiso",
								   ".bmp");

	cout << "archivo ejecutado!";

	return 0;
}
