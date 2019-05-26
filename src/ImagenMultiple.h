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
	/*
	 * post: es creado un objeto ImagenMultiple vacío.
	 */
	ImagenMultiple();

	/*
	 * pre: el operador << esta sobrecargado para emplear el tipo T.
	 * post: el tipo T está convertido a string.
	 */
	template <typename T> string convertirEnStr( const T & t );

	/*
	 * pre: carga las imagenes que se encuentran en la ruta path, y que llevan una numeracion
	 * 		en su nombre de archivo compuesto por el nombrebase + numeracion + extension (.bmp)
	 * post: las imagenes son cargadas en memoria dinamica, en caso de no encontrar la cantidad
	 * 		 indicada de archivos con el formato indicado devuelve false.
	 */
	bool cargarImagenMultiple(string path, string nombrebase, int cantidad, string extension);
	/*
	 * pre: El objeto ImagenMultiple ha sido creado previamente pero ninguna imagen fue cargada.
	 * 		En caso de que alguna imagen haya sido cargada desde los archivos, devuelve false y no
	 * 		modifica el objeto. Si previamente fueron cargados objetos, libera la memoria pedida y
	 * 		crea la cantidad de imagenes solicitada.
	 * post: queda actualizado el atributo "cantidad" del objeto 'this',asi como también la memoria
	 * 		reservada para la cantidad especificada.
	 */
	bool crearImagenMultiple(int cantidad);
	/*
	 * pre: los atributos "bmp" del objeto 'this' ya fueron cargados con éxito y ya se realizaron todas
	 * 		las operaciones que habían de ser realizadas.
	 * post:	las imágenes guardadas en memoria por el objeto 'this' son guardadas en el disco
	 * 			como ficheros individuales.
	 */
	bool guardarImagenes(string path, string nombrebase, string extension);

	/*
	 * pre: las imagenes fueron cargadas desde archivo, por lo que los atributos path, nombrebase,
	 * 		extension y cantidad, no fueron modificados. Entonces no hace falta cambiarlos.
	 * post: las imagenes almacenadas en memoria por el objeto 'this' son guardadas en el disco, en la
	 * 		 ruta especificada previamente, en archivos indivuales numerados.
	 */
	bool guardarImagenes();

	/*
	 * pre: La ImagenMultiple fue previamente generada sin cargar archivos desde el disco.
	 * post: Es establecido el ancho y el alto de todas las bmp guardadas en el vector de
	 * 		 imágenes que está en this->bmp[]
	 */
	bool establecerTamanio(int width, int height);

	/*
	 * pre: la imagen fue cargada de un archivo exitosamente o bien fue creada en memoria y el tamanio
	 * 		fue ingresado manualmente por "establecerTamanio()".
	 * post: devuelve el valor del ancho de las imagenes almacenadas en 'this'.
	 */
	int obtenerAncho();

	/*
	 * pre: la imagen fue cargada de un archivo exitosamente o bien fue creada en memoria y el tamanio
	 * 		fue ingresado manualmente por "establecerTamanio()".
	 * post: devuelve el valor del alto de las imagenes almacenadas en 'this'.
	 */
	int obtenerAlto();

	/*
	 * pre: la imagen fue previamente cargada del disco o creada en memoria por el metodo
	 * 		"crearImagenMultiple()".
	 * post: devuelve el puntero a una de las imagenes creada en tiempo de ejecucion / cargada
	 * 		 de archivos.
	 */
	BMP* obtenerImagen(int numero);

	/*
	 * post: borra de memoria dinámica los objetos creados previamente.
	 */
	~ImagenMultiple();

	/*
	 * pre: hay un tablero con fichas almacenadas y una imagen modelo distinta para representar
	 * 		cada una de las fichas de los jugadores, ambos objetos son parámetros del método.
	 * post: en el conjunto de imágenes del objeto 'this' son generadas las vistas de planta
	 * 		para cada uno de los niveles del tablero.
	 */
	void generarVistaEnNivelesXY(ImagenMultiple* aInsertar, Tablero *elTableroDeUnTest);

	/*
	 * pre: son ingresados el número de imagen base que está dentro del conjunto de imágenes
	 * 		del objeto 'this'. También es ingresado un puntero de la imagen a insertar en la imagen
	 * 		base. Son especificadas las posiciones de inserción y el ancho y alto de la imagen a insertar.
	 * 		En caso de salir fuera del rango de píxeles de la imagen devuelve false.
	 * post: la imagen a insertar es copiada en la posición especificada de la imagen base.
	 */
	bool insertarImagen(int nroElemento, BMP *fragment, int x, int y, int width, int height);

};

} /* namespace std */

#endif /* IMAGENMULTIPLE_H_ */
