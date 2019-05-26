
#include "Ficha.h"

Ficha::Ficha(int numero){

	this->numero = numero;
	for (int i = 0; i < 3; i++) {
		this->color[i] = (rand()%256);
	}
}


int Ficha::darNumero(){

	return this->numero;
}


Ficha::~Ficha(){

}
