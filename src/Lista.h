
#ifndef LISTA_H_
#define LISTA_H_

#include "Nodo.h"


/*
 * Una Lista es una colecci�n din�mica de elementos dispuestos en una secuencia.
 *
 * Define operaciones para agregar, remover, acceder y cambiar elementos
 * en cualquier posici�n.
 *
 * Tiene un cursor que permite recorrer todos los elementos secuencialmente.
 *
 */

template<class T>
class Lista {

    private:

		// Puntero al primer elemento de la lista
        Nodo<T>* primero;

        // Tama�o de mi lista
        unsigned int tamanio;
        Nodo<T>* cursor;

    public:

        /* Constructor sin argumentos.
         *
         * PRE: -
         * POST: construye una lista vac�a.
         * - primero y cursor apuntan a NULL
         * - tama�o = 0
         */
        Lista();


        /* Constructor que copia una lista existente.
         *
         * PRE: -
         * POST: Una Lista que tiene los mismos elementos que otraLista.
         *       La instancia resulta en una copia de otraLista.
         */
        Lista(Lista<T>& otraLista);


        /* Indica si la lista esta vacia.
         *
         * PRE: Lista creada.
         * POST: arroja un booleano que indica si la Lista tiene alg�n elemento.
         */
        bool estaVacia();


        /* Obtener el tama�o de la lista.
         *
         * PRE: Lista creada.
         * POST: devuelve la cantidad de elementos que tiene la Lista.
         */
        unsigned int contarElementos();


        /* Agregar un elemento al final de la Lista.
         *
         * PRE: Lista creada y elemento valido.
         * POST: Agrega el elemento al final de la Lista, en la posici�n:
         *       contarElementos() + 1.
         */
        void agregar(T elemento);


        /* Agregar un elemento a la Lista en una posicion dada.
         *
         * PRE: Lista creada, elemento valido,
         * 		posici�n pertenece al intervalo: [1, contarElementos() + 1]
         * POST: Agrega el elemento en la posici�n indicada.
         *
         */
        void agregar(T elemento, unsigned int posicion);


        /* Copiar elementos de otraLista al final de mi Lista.
         *
         * PRE: Lista creada.
         * post: agrega todos los elementos de otraLista
         *       a partir de la posici�n contarElementos() + 1.
         */
        void agregar(Lista<T> &otraLista);


        /* Obtener un elemento de Lista indicando su posici�n.
         *
         * PRE: posicion pertenece al intervalo: [1, contarElementos()]
         * POST: Devuelve el elemento en la posici�n indicada.
         */
        T obtener(unsigned int posicion);


        /* Cambio un elemento de Lista en la posicion dada por elemento.
         *
         * PRE: posicion pertenece al intervalo: [1, contarElementos()]
         * POST: Cambia el elemento en la posici�n indicada por el
         *       elemento dado.
         */
        void asignar(T elemento, unsigned int posicion);


        /* Elimino un elemento de la lista en la posicion dada.
         *
         * pre: posiciOn pertenece al intervalo: [1, contarElementos()]
         * post: Remueve de la Lista el elemento en la posici�n indicada.
         */
        void remover(unsigned int posicion);


        /* Colocar cursor apuntando a NULL.
         *
         * PRE: Lista creada.
         * POST: deja el cursor de la Lista apuntando a NULL.
         */
        void iniciarCursor();


        /* Avanzar cursor un elemento en la Lista.
         *
         * PRE: se ha iniciado un recorrido (invocando el m�todo
         *       iniciarCursor()) y desde entonces no se han agregado o
         *       removido elementos de la Lista.
         * POST: mueve el cursor y lo posiciona en el siguiente elemento
         *       del recorrido.
         *       El valor de retorno indica si el cursor qued� posicionado
         *       sobre un elemento o no (en caso de que la Lista est� vac�a o
         *       no existan m�s elementos por recorrer.)
         */
        bool avanzarCursor();


        /* Obtener elemento al que apunta el Cursor.
         *
         * PRE: el cursor est� posicionado sobre un elemento de la Lista,
         *       (fue invocado el m�todo avanzarCursor() y devolvi� true)
         * POST: devuelve el elemento en la posici�n del cursor.
         *
         */
        T obtenerCursor();


        /* Destructor.
         *
         * PRE: Lista creada.
         * POST: Libera los recursos asociados a la Lista.
         */
        ~Lista();

    private:

        /* Obtener nodo en posicion solicitada.
         *
         * PRE: posici�n pertenece al intervalo: [1, contarElementos()]
         * POST: devuelve el nodo en la posici�n indicada.
         */
        Nodo<T>* obtenerNodo(unsigned int posicion); // NOTA: primitiva PRIVADA
};


/*
 * Excepci�n que representa el intento de acceder a un elemento
 * que no existe dentro de la Lista.
 */
class ExcepcionElementoInexistente {

    private:
        unsigned int posicion;

    public:
        /* Constructor.
         *
         * PRE: -
         * POST: Excepci�n creada a partir de la posici�n inv�lida a la
         *       que se intent� acceder.
         */
        ExcepcionElementoInexistente(unsigned int posicion) {

            this->posicion = posicion;
        }

        /*
         * post: devuelve la posici�n inv�lida a la que se intent� acceder.
         */
        unsigned int obtenerPosicionInvalida() {

            return this->posicion;
        }
};


// Constructor sin argumentos.
template<class T>
Lista<T>::Lista() {

    this->primero = NULL;
    this->tamanio = 0;
    this->cursor = NULL;
}


// Constructor que copia una lista existente.
template<class T>
Lista<T>::Lista(Lista<T>& otraLista) {

    this->primero = NULL;
    this->tamanio = 0;
    this->cursor = NULL;

    /* copia los elementos de otraLista */
    this->agregar(otraLista);
}


// Indica si la lista esta vacia.
template<class T>
bool Lista<T>::estaVacia() {

	return (this->tamanio == 0);
}


// Obtener el tama�o de la lista.
template<class T>
unsigned int Lista<T>::contarElementos() {

    return this->tamanio;
}


// Agregar un elemento al final de la Lista.
template<class T>
void Lista<T>::agregar(T elemento) {

    this->agregar(elemento, this->contarElementos() + 1);
}


// Agregar un elemento a la Lista en una posicion dada.
template<class T>
void Lista<T>::agregar(T elemento, unsigned int posicion) {

    if ((posicion > 0) && (posicion <= this->contarElementos() + 1)) {

        Nodo<T>* nuevo = new Nodo<T>(elemento);

        if (posicion == 1) {

            nuevo->cambiarSiguiente(this->primero);
            this->primero = nuevo;

        } else {

            Nodo<T>* anterior = this->obtenerNodo(posicion - 1);
            nuevo->cambiarSiguiente(anterior->obtenerSiguiente());
            anterior->cambiarSiguiente(nuevo);
        }

        this->tamanio++;

        /* cualquier recorrido actual queda invalidado */
        this->iniciarCursor();

    } else {

        throw ExcepcionElementoInexistente(posicion);
    }
}


// Copiar elementos de otraLista al final de mi Lista.
template<class T>
void Lista<T>::agregar(Lista<T> &otraLista) {

    otraLista.iniciarCursor();

    while (otraLista.avanzarCursor()) {

        this->agregar(otraLista.obtenerCursor());
    }
}


// Obtener un elemento de Lista indicando su posici�n.
template<class T>
T Lista<T>::obtener(unsigned int posicion) {

    T elemento;

    if ((posicion > 0) && (posicion <= this->contarElementos())) {

        elemento = this->obtenerNodo(posicion)->obtenerDato();

    } else {

        throw ExcepcionElementoInexistente(posicion);
    }

    return elemento;
}


// Cambio un elemento de Lista en la posicion dada por elemento.
template<class T>
void Lista<T>::asignar(T elemento, unsigned int posicion) {

    if ((posicion > 0) && (posicion <= this->contarElementos())) {

        this->obtenerNodo(posicion)->cambiarDato(elemento);

    } else {

        throw ExcepcionElementoInexistente(posicion);
    }
}


// Elimino un elemento de la lista en la posicion dada.
template<class T>
void Lista<T>::remover(unsigned int posicion) {

    if ((posicion > 0) && (posicion <= this->contarElementos())) {

        Nodo<T>* removido;

        if (posicion == 1) {

            removido = this->primero;
            this->primero = removido->obtenerSiguiente();

        } else {

            Nodo<T>* anterior = this->obtenerNodo(posicion - 1);
            removido = anterior->obtenerSiguiente();
            anterior->cambiarSiguiente(removido->obtenerSiguiente());
        }

        delete removido;
        this->tamanio--;

        /* cualquier recorrido actual queda invalidado */
        this->iniciarCursor();

    } else {

        throw ExcepcionElementoInexistente(posicion);
    }
}


// Colocar cursor apuntando a NULL.
template<class T>
void Lista<T>::iniciarCursor() {

    this->cursor = NULL;
}


// Avanzar cursor un elemento en la Lista.
template<class T>
bool Lista<T>::avanzarCursor() {

    if (this->cursor == NULL) {

        this->cursor = this->primero;

    } else {

        this->cursor = this->cursor->obtenerSiguiente();
    }

    /* pudo avanzar si el cursor ahora apunta a un nodo */
    return (this->cursor != NULL);
}


// Obtener elemento al que apunta el Cursor.
template<class T>
T Lista<T>::obtenerCursor() {

    T elemento;

    if (this->cursor != NULL) {

        elemento = this->cursor->obtenerDato();

    } else {

        throw ExcepcionElementoInexistente(0);
    }

    return elemento;
}


// Destructor.
template<class T>
Lista<T>::~Lista() {

    while (this->primero != NULL) {

        Nodo<T>* aBorrar = this->primero;
        this->primero = this->primero->obtenerSiguiente();

        delete aBorrar;
    }
}


// Obtener nodo en posicion solicitada.
template<class T>
Nodo<T>* Lista<T>::obtenerNodo(unsigned int posicion) {

    Nodo<T>* actual = this->primero;
    for (unsigned int i = 1; i < posicion; i++) {

        actual = actual->obtenerSiguiente();
    }

    return actual;
}


#endif /* LISTA_H_ */
