/*
 * Imagen.h
 *
 *  Created on: May 23, 2019
 *      Author: root
 */

#ifndef IMAGENMULTIPLE_H_
#define IMAGENMULTIPLE_H_

#include "EasyBMP.h"
#include <iostream>
#include <sstream>
#include "Tablero.h"


namespace std {

class ImagenMultiple {
private:
	BMP **bmp;
	string path;
	string nombreBase;
	string extension;
	int cantidad;
	bool imagenMultipleCargada;
public:
	ImagenMultiple() {
		this->bmp = NULL;
		this->path = "";
		this->nombreBase = "";
		this->extension = "";
		this->cantidad = 0;
	}
	template <typename T> string convertirEnStr( const T & t ) {
	   ostringstream os;
	   os << t;
	   return os.str();
	}
	// ¿si cantidad = 0 ?
	bool cargarImagenMultiple(string path, string nombrebase, int cantidad, string extension) {
		this->cantidad = cantidad;
		this->bmp = new BMP*[cantidad];
		this->imagenMultipleCargada = true;
		for (int i = 0; i< cantidad; i++) {
			bmp[i] = new BMP();
			string str = path + nombrebase + this->convertirEnStr(i+1) + extension;
			const char *c = str.c_str();
			if (!bmp[i]->ReadFromFile(c)) {
				this->imagenMultipleCargada = false;
			}
		}
		return this->imagenMultipleCargada;
	}
	bool crearImagenMultiple(int cantidad) {
		if (cantidad == 0) {return false;}

		if (this->bmp == NULL ) {
			this->bmp = new BMP*[cantidad];
			for (int i = 0; i< cantidad; i++) {
				this->bmp[i] = new BMP();
			}
		}
		else if (this->cantidad != cantidad) { //this->bmp != NULL   // si this->cantidad != cantidad && this->cantidad !=0
			for (int i = 0; i<this->cantidad;i++){
				delete this->bmp[i];
			}
			delete [] this->bmp;
			this->bmp = NULL;
			this->crearImagenMultiple(cantidad); //llamo nuevamente el método, ahora para crear arreglo dinámico.
		}
		// si this->cantidad == cantidad, y this->bmp != NULL, el objeto fue creado por cargarImagenMultiple.
		this->cantidad = cantidad;
		return true;
	}
	bool guardarImagenes(string path, string nombrebase, string extension) {
		for (int i = 0; i< this->cantidad; i++) {
			string str = path + nombrebase + this->convertirEnStr(i+1) + extension;
			const char *c = str.c_str();
			if (!this->bmp[i]->WriteToFile(c)) {
				return false;
			}
		}
		return true;
	}
	bool guardarImagenes() {
		if (this->imagenMultipleCargada) {
			for (int i = 0; i< this->cantidad; i++) {
				string str = this->path + this->nombreBase + this->convertirEnStr(i+1) + this->extension;
				const char *c = str.c_str();
				if (!this->bmp[i]->WriteToFile(c)) {
					return false;
				}
			}
		}
		return this->imagenMultipleCargada;
	}
	bool establecerTamanio(int width, int height) {
		if (! this->imagenMultipleCargada ) {
			for (int i=0; i<this->cantidad; i++){
				this->bmp[i]->SetSize(width, height);
			}
		}
		return !(this->imagenMultipleCargada);
	}
	int obtenerAncho(){
		return (this->bmp[0]->TellWidth());
	}
	int obtenerAlto() {
		return (this->bmp[0]->TellHeight());
	}
	BMP* obtenerImagen(int numero) {
		return this->bmp[numero];
	}
	~ImagenMultiple() {
		for (int i=0; i<this->cantidad; i++){
			delete  this->bmp[i];
		}
		delete [] this->bmp;
	}
	void generarVistaEnNivelesXY(ImagenMultiple* aInsertar, Tablero *elTableroDeUnTest) {
		int unaUbicacionEnTablero[3] = {0,0,0};
		int numeroDeFicha = 0;
		int *dimensionesTablero = elTableroDeUnTest->darTamanio();

		if (this->cantidad != dimensionesTablero[2]) {
			this->crearImagenMultiple(dimensionesTablero[2]);
		}

		this->establecerTamanio(dimensionesTablero[0] * aInsertar->obtenerAncho(),
								dimensionesTablero[1] * aInsertar->obtenerAlto());

		for (int iii = 0; iii<dimensionesTablero[2]; iii++){
			for (int i = 0; i<dimensionesTablero[0]; i++) {
				for (int ii=0; ii<dimensionesTablero[1]; ii++) {
					unaUbicacionEnTablero[0] = (i+1);
					unaUbicacionEnTablero[1] = (ii+1);
					unaUbicacionEnTablero[2] = (iii+1);
					if (elTableroDeUnTest->posicionVacia(unaUbicacionEnTablero)) {
						numeroDeFicha = elTableroDeUnTest->obtenerFicha(unaUbicacionEnTablero)->darNumero();
						RangedPixelToPixelCopy(*(aInsertar->obtenerImagen(numeroDeFicha-1)),
								0, aInsertar->obtenerAncho()-1,
								0, aInsertar->obtenerAlto()-1,
								*(this->obtenerImagen(iii)),
								aInsertar->obtenerAncho() * i, aInsertar->obtenerAlto() * ii);
						/*this->insertarImagen(iii,						  //nro de elemento en this->bmp[iii]
											 aInsertar->obtenerImagen(numeroDeFicha-1), //imagen de la ficha.
											 aInsertar->obtenerAncho()*i, //posicion horizontal de la ficha
											 aInsertar->obtenerAlto()*ii, //posicion vertical de la ficha
											 aInsertar->obtenerAncho(),	  //ancho de la ficha a insertar
											 aInsertar->obtenerAlto());   */ //alto de la icha a insertar
					}
				}
			}
		}
	}
	bool insertarImagen(int nroElemento, BMP *fragment, int x, int y, int width, int height) { // pre: i< base->TellWidth()
		for (int i = x; i< ( x+width ); i++) {
			for (int j = y; j< ( y+height ); j++ ) {
					this->obtenerImagen(nroElemento)->SetPixel( i, j, fragment->GetPixel(i-x,j-y) );
			}
		}
		return true;
	}
};

} /* namespace std */

#endif /* IMAGENMULTIPLE_H_ */
