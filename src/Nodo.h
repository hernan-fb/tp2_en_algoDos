
#ifndef NODO_H_
#define NODO_H_

#ifndef NULL
#define NULL 0
#endif


template<class T>
class Nodo {

	private:

        T dato;
        Nodo<T>* siguiente;

    public:

        /* Constructor con parametro.
         *
         * PRE: -
         * POST: el Nodo resulta inicializado con el dato dado
         *       y un puntero a NULL.
         */
        Nodo(T dato);


        /* Obtener el dato almacenado en el nodo.
         *
         * PRE: Nodo creado.
         * POST: devuelve el dato que contiene el nodo.
         */
        T obtenerDato();


        /* Setea el dato del nodo (lo cambia).
         *
         * PRE: Nodo creado; nuevoDato debe ser un dato válido.
         * POST: cambia el valor del dato.
         */
        void cambiarDato(T nuevoDato);


        /* Obtener el puntero al nodo siguiente.
         *
         * PRE: Nodo creado.
         * POST: Devuelve el puntero al siguiente nodo.
         */
        Nodo<T>* obtenerSiguiente();


        /* Cambiar nodo siguiente.
         *
         * PRE: Nodo creado.
         * POST: cambia el siguiente Nodo por nuevoSiguiente.
         */
        void cambiarSiguiente(Nodo<T>* nuevoSiguiente);


        /* Destructor.
         *
         * PRE: Nodo creado.
         * POST: No hace nada.
         */
        ~Nodo();

};


// Constructor con parametro.
template <class T>
Nodo<T>::Nodo(T dato) {

	this->dato = dato;
	this->siguiente = NULL;
}


// Obtener el dato almacenado en el nodo.
template <class T>
T Nodo<T>::obtenerDato() {

	return this->dato;
}


// Setea el dato del nodo (lo cambia).
template <class T>
void Nodo<T>::cambiarDato(T nuevoDato) {

	this->dato = nuevoDato;
}


// Obtener el puntero al nodo siguiente.
template <class T>
Nodo<T>* Nodo<T>::obtenerSiguiente() {

	return this->siguiente;
}


// Cambiar nodo siguiente.
template <class T>
void Nodo<T>::cambiarSiguiente(Nodo<T>* nuevoSiguiente) {

    this->siguiente = nuevoSiguiente;
}


// Destructor.
template <class T>
Nodo<T>::~Nodo(){
	// No hace nada.
}


#endif /* NODO_H_ */
