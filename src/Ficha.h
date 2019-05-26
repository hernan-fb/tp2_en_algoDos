
#ifndef FICHA_H_
#define FICHA_H_

#include <cstdlib>

class Ficha{

private:

	int numero;
	int color[3];

public:

	/* Constructor
	 *
	 * PRE: -
	 * POST: Crea una Ficha lista para su uso.
	 */
	Ficha(int numero);


	/* Dar numero de jugador.
	 *
	 * PRE: -
	 * POST: Devuelve el numero del jugador al que corresponde esta ficha.
	 */
	int darNumero();


	/* Destructor.
	 *
	 * PRE: -
	 * POST: Libera los recursos solicitados.
	 */
	~Ficha();

};



#endif /* FICHA_H_ */
