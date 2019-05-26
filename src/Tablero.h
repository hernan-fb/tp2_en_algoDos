/*
 * Tablero.h
 *
 *  Created on: May 23, 2019
 *      Author: root
 */

#ifndef TABLERO_H_
#define TABLERO_H_

#include "Lista.h"
//#include "Consola.h"
#include <string>
#include <algorithm>
#include "Ficha.h"

using std::string;

//class Consola;

struct Celda;

class Tablero {

private:
	int tamanio[3];
	Lista<Lista<Lista<Celda*>*>*>* filas;

public:
	Tablero(int tamanio[3]);
	int* darTamanio();
	bool hileraLlena(int ubicacion[3]);
	void guardarFicha(Ficha* ficha, int ubicacion[3]);
	bool posicionVacia(int posicion[3]);
	Ficha* obtenerFicha(int posicion[3]);
	void avanzarFilaHasta(int posicionFinal);
	void avanzarColumnaHasta(int posicionFinal);
	bool avanzarPisoHasta(int posicionFinal);
};


#endif /* TABLERO_H_ */
