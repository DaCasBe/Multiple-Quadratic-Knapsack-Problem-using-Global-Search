/*
 * MKPSimpleBestImprovementNO.h
 *
 *  Created on: Jan 29, 2017
 *      Author: carlos
 */

#ifndef INCLUDE_MQKPSIMPLEBESTIMPROVEMENTNO_H_
#define INCLUDE_MQKPSIMPLEBESTIMPROVEMENTNO_H_

#include <MQKPNeighExplorer.h>
#include <MQKPSolution.h>
#include <MQKPChangeOperation.h>
/**
 * Clase que se encarga de explorar el vecindario de una solución dada, devolviendo la mejor operación de asignación de un objeto a una mochila entre las operaciones posibles, devolverá FALSE si la operación devuelta no mejora a la solución actual
 */
class MQKPSimpleBestImprovementNO : public MQKPNeighExplorer{

public:

	/**
	 * Destructor
	 */
	virtual ~MQKPSimpleBestImprovementNO(){

	}

	/**
	 * Función que explora el vecindario de una solución dada, devolviendo la mejor operación de asignación de un objeto a una mochila entre las operaciones posibles, devolverá FALSE si la operación devuelta no mejora a la solución actual
	 * @param[in] instance Instancia del problema
	 * @param[in] solution Solución cuya vecindad se va a explorar
	 * @param[out] operation Operación tal que aplicada a la solución, devuelve una vecina.
	 *
	 * @return true si la operación devuelta mejora a solution; false, si no hay ninguna operación en la vecindad que pueda mejorar a solution
	 */
	virtual bool findOperation(MQKPInstance &instance, MQKPSolution &solution, MQKPChangeOperation &operation);

};


#endif /* INCLUDE_MQKPSIMPLEBESTIMPROVEMENTNO_H_ */
