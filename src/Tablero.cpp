/*
 * Tablero.cpp
 *
 *  Created on: May 23, 2019
 *      Author: root
 */

#include "Tablero.h"

struct Celda {
	Ficha* contenido;
	Celda* portal;
	int ubicacion[3];
};

Tablero::Tablero(int tamanio[3]){

	for(int i = 0; i < 3; i++){
		this->tamanio[i] = tamanio[i];
	}

	this->filas = new Lista<Lista<Lista<Celda*>*>*>;

	for(int i=1; i <= this->tamanio[0]; i++){
		this->filas->agregar(new Lista<Lista<Celda*>*>);
	}

	this->filas->iniciarCursor();
	while(this->filas->avanzarCursor()){
		for (int j=1; j <= this->tamanio[1]; j++){
			this->filas->obtenerCursor()->agregar(new Lista<Celda*>);
		}
	}
}
int* Tablero::darTamanio(){

	return this->tamanio;
}
bool Tablero::hileraLlena(int ubicacion[3]){

	int& filaSolicitada = ubicacion[0];
	int& columnaSolicitada = ubicacion[1];

	this->avanzarFilaHasta(filaSolicitada);
	this->avanzarColumnaHasta(columnaSolicitada);

	Lista<Celda*>* pisos = this->filas->obtenerCursor()->obtenerCursor();
	return ((int)pisos->contarElementos() == this->tamanio[2]);
}
void Tablero::guardarFicha(Ficha* ficha, int ubicacion[3]){

	/*if(this->hileraLlena(ubicacion)){
		throw string("La hilera donde se quizo guardar la ficha estaba llena.");
	}*/

	int& fila = ubicacion[0];
	int& columna = ubicacion[1];

	this->avanzarFilaHasta(fila);
	this->avanzarColumnaHasta(columna);

	Lista<Celda*>* pisos = this->filas->obtenerCursor()->obtenerCursor();
	ubicacion[2] = pisos->contarElementos();
	Celda *celdita = new Celda;
	celdita->contenido = ficha;
	celdita->ubicacion[0] = ubicacion[0];
	celdita->ubicacion[1] = ubicacion[1];
	celdita->ubicacion[2] = ubicacion[2];
	pisos->agregar(celdita);	//atencion, hacer cambio por la version original new Celda(ficha,ubicacion)
	ubicacion[2]++;
}
bool Tablero::posicionVacia(int posicion[3]){
	this->avanzarFilaHasta(posicion[0]);
	this->avanzarColumnaHasta(posicion[1]);
	return (this->avanzarPisoHasta(posicion[2]));
}
Ficha* Tablero::obtenerFicha(int posicion[3]){
	this->avanzarFilaHasta(posicion[0]);
	this->avanzarColumnaHasta(posicion[1]);
	this->avanzarPisoHasta(posicion[2]);
	return(filas->obtenerCursor()->obtenerCursor()->obtenerCursor()->contenido); //atencion, hacer cambio por el método verContenido()
}
void Tablero::avanzarFilaHasta(int posicionFinal){

	this->filas->iniciarCursor();
	for(int fila = 1; fila <= posicionFinal; fila++){
		this->filas->avanzarCursor();
	}
}
void Tablero::avanzarColumnaHasta(int posicionFinal){

	this->filas->obtenerCursor()->iniciarCursor();
	for(int columna = 1; columna <= posicionFinal; columna++){
		this->filas->obtenerCursor()->avanzarCursor();
	}
}

bool Tablero::avanzarPisoHasta(int posicionFinal){

	Lista<Celda*>* pisos = this->filas->obtenerCursor()->obtenerCursor();
	pisos->iniciarCursor();
	int piso = 0;

	while(piso < posicionFinal && pisos->avanzarCursor()){
		piso++;
	}

	return (piso == posicionFinal);
}
