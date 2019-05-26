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
public:
	ImagenMultiple() {
		this->path = "";
		this->nombreBase = "";
		this->extension = "";
	}
	template <typename T> string convertirEnStr( const T & t ) {
	   ostringstream os;
	   os << t;
	   return os.str();
	}
	bool cargarImagenes(string path, string nombrebase, int cantidad, string extension) {
		this->cantidad = cantidad;
		bmp = new BMP*[cantidad];
		for (int i = 0; i< cantidad; i++) {
			bmp[i] = new BMP();
			string str = path + nombrebase + this->convertirEnStr(i+1) + extension;
			const char *c = str.c_str();
			if (!bmp[i]->ReadFromFile(c)) {
				return false;
			}
		}
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
		for (int i = 0; i< this->cantidad; i++) {
			string str = this->path + this->nombreBase + this->convertirEnStr(i+1) + this->extension;
			const char *c = str.c_str();
			if (!this->bmp[i]->WriteToFile(c)) {
				return false;
			}
		}
		return true;
	}
	bool establecerTamanio(int width, int height) {
		if ( !(this->path == "") ) {
			for (int i=0; i<this->cantidad; i++){
				bmp[i]->SetSize(width, height);
			}
		}
		return !(this->path == "");
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
		int numeroDeFicha;
		int *dimensionesTablero;
		dimensionesTablero = elTableroDeUnTest->darTamanio();

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
						this->insertarImagen(iii,						  //nro de elemento en this->bmp[iii]
											 aInsertar->obtenerImagen(numeroDeFicha-1), //imagen de la ficha.
											 aInsertar->obtenerAncho()*i, //posicion horizontal de la ficha
											 aInsertar->obtenerAlto()*ii, //posicion vertical de la ficha
											 aInsertar->obtenerAncho(),	  //ancho de la ficha a insertar
											 aInsertar->obtenerAlto());   //alto de la icha a insertar
					}
				}
			}
		}
	}
	bool insertarImagen(int nroElemento, BMP *fragment, int x, int y, int width, int height) { // pre: i< base->TellWidth()
		for (int i = x; i< ( x+width ); i++) {
			for (int j = y; j< ( y+height ); j++ ) {
					this->bmp[nroElemento]->SetPixel( i, j, fragment->GetPixel(i-x,j-y) );
			}
		}
		return true;
	}
};

} /* namespace std */

#endif /* IMAGENMULTIPLE_H_ */
