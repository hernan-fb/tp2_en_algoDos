/*
 * Imagen.cpp
 *
 *  Created on: May 23, 2019
 *      Author: root
 */

#include "ImagenMultiple.h"

namespace std {
ImagenMultiple::ImagenMultiple() {
	this->bmp = NULL;
	this->path = "";
	this->nombreBase = "";
	this->extension = "";
	this->cantidad = 0;
	this->imagenMultipleCargada = false;
}

/*
 * pre: el operador << esta sobrecargado para emplear el tipo T.
 * post: el tipo T está convertido a string.
 */
template <typename T> string ImagenMultiple::convertirEnStr( const T & t ) {
   ostringstream os;
   os << t;
   return os.str();
}

/*
 * pre: carga las imagenes que se encuentran en la ruta path, y que llevan una numeracion
 * 		en su nombre de archivo compuesto por el nombrebase + numeracion + extension (.bmp)
 * post: las imagenes son cargadas en memoria dinamica, en caso de no encontrar la cantidad
 * 		 indicada de archivos con el formato indicado devuelve false.
 */
bool ImagenMultiple::cargarImagenMultiple(string path, string nombrebase, int cantidad, string extension) {
	if (cantidad == 0) {return false;}
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

/*
 * pre: El objeto ImagenMultiple ha sido creado previamente pero ninguna imagen fue cargada.
 * 		En caso de que alguna imagen haya sido cargada desde los archivos, devuelve false y no
 * 		modifica el objeto. Si previamente fueron cargados objetos, libera la memoria pedida y
 * 		crea la cantidad de imagenes solicitada.
 * post: queda actualizado el atributo "cantidad" del objeto 'this',asi como también la memoria
 * 		reservada para la cantidad especificada.
 */
bool ImagenMultiple::crearImagenMultiple(int cantidad) {
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

/*
 * pre: los atributos "bmp" del objeto 'this' ya fueron cargados con éxito y ya se realizaron todas
 * 		las operaciones que habían de ser realizadas.
 * post:	las imágenes guardadas en memoria por el objeto 'this' son guardadas en el disco
 * 			como ficheros individuales.
 */
bool ImagenMultiple::guardarImagenes(string path, string nombrebase, string extension) {
	for (int i = 0; i< this->cantidad; i++) {
		string str = path + nombrebase + this->convertirEnStr(i+1) + extension;
		const char *c = str.c_str();
		if (!this->bmp[i]->WriteToFile(c)) {
			return false;
		}
	}
	return true;
}

/*
 * pre: las imagenes fueron cargadas desde archivo, por lo que los atributos path, nombrebase,
 * 		extension y cantidad, no fueron modificados. Entonces no hace falta cambiarlos.
 * post: las imagenes almacenadas en memoria por el objeto 'this' son guardadas en el disco, en la
 * 		 ruta especificada previamente, en archivos indivuales numerados.
 */
bool ImagenMultiple::guardarImagenes() {
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

/*
 * pre: La ImagenMultiple fue previamente generada sin cargar archivos desde el disco.
 * post: Es establecido el ancho y el alto de todas las bmp guardadas en el vector de
 * 		 imágenes que está en this->bmp[]
 */
bool ImagenMultiple::establecerTamanio(int width, int height) {
	if (! this->imagenMultipleCargada ) {
		for (int i=0; i<this->cantidad; i++){
			this->bmp[i]->SetSize(width, height);
		}
	}
	return !(this->imagenMultipleCargada);
}

/*
 * pre: la imagen fue cargada de un archivo exitosamente o bien fue creada en memoria y el tamanio
 * 		fue ingresado manualmente por "establecerTamanio()".
 * post: devuelve el valor del ancho de las imagenes almacenadas en 'this'.
 */
int ImagenMultiple::obtenerAncho(){
	return (this->bmp[0]->TellWidth());
}

/*
 * pre: la imagen fue cargada de un archivo exitosamente o bien fue creada en memoria y el tamanio
 * 		fue ingresado manualmente por "establecerTamanio()".
 * post: devuelve el valor del alto de las imagenes almacenadas en 'this'.
 */
int ImagenMultiple::obtenerAlto() {
	return (this->bmp[0]->TellHeight());
}

/*
 * pre: la imagen fue previamente cargada del disco o creada en memoria por el metodo
 * 		"crearImagenMultiple()".
 * post: devuelve el puntero a una de las imagenes creada en tiempo de ejecucion / cargada
 * 		 de archivos.
 */
BMP* ImagenMultiple::obtenerImagen(int numero) {
	return this->bmp[numero];
}

/*
 * post: borra de memoria dinámica los objetos creados previamente.
 */
ImagenMultiple::~ImagenMultiple() {
	for (int i=0; i<this->cantidad; i++){
		delete  this->bmp[i];
	}
	delete [] this->bmp;
}

/*
 * pre: hay un tablero con fichas almacenadas y una imagen modelo distinta para representar
 * 		cada una de las fichas de los jugadores, ambos objetos son parámetros del método.
 * post: en el conjunto de imágenes del objeto 'this' son generadas las vistas de planta
 * 		para cada uno de los niveles del tablero.
 */
void ImagenMultiple::generarVistaEnNivelesXY(ImagenMultiple* aInsertar, Tablero *elTableroDeUnTest) {
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
					/*RangedPixelToPixelCopy(*(aInsertar->obtenerImagen(numeroDeFicha-1)),
							0, aInsertar->obtenerAncho()-1,
							0, aInsertar->obtenerAlto()-1,
							*(this->obtenerImagen(iii)),
							aInsertar->obtenerAncho() * i, aInsertar->obtenerAlto() * ii); */
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

/*
 * pre: son ingresados el número de imagen base que está dentro del conjunto de imágenes
 * 		del objeto 'this'. También es ingresado un puntero de la imagen a insertar en la imagen
 * 		base. Son especificadas las posiciones de inserción y el ancho y alto de la imagen a insertar.
 * 		En caso de salir fuera del rango de píxeles de la imagen devuelve false.
 * post: la imagen a insertar es copiada en la posición especificada de la imagen base.
 */
bool ImagenMultiple::insertarImagen(int nroElemento, BMP *fragment, int x, int y, int width, int height) { // pre: i< base->TellWidth()
	for (int i = x; i< ( x+width ); i++) {
		for (int j = y; j< ( y+height ); j++ ) {
				this->obtenerImagen(nroElemento)->SetPixel( i, j, fragment->GetPixel(i-x,j-y) );
		}
	}
	return true;
}
} /* namespace std */
