/**
 * MQKPSolution.h
 * 
 * Fichero que define la clase MQKPSolution. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef __MQKPSOLUTION_H__
#define __MQKPSOLUTION_H__

#ifndef __MQKPINSTANCE_H__
#include "MQKPInstance.h"
#else
class MQKPInstance;
#endif

/**
 * Clase que representa una solución al problema
 *
 * Sobre la representación de soluciones:
 * La representación de las soluciones será un vector de número enteros: de 1 a M para objetos que están en alguna de las M mochilas y 0 para objetos que no están en ninguna mochilas
 */
class MQKPSolution {
protected:
	/* Definir las variables miembro
	 * _sol Vector de enteros que será la representación interna de la solución al problema
	 * _numObjs Entero donde se almacenará el número de objetos del problema
	 * _fitness valor double que almacena la calidad de la solución
	 */
	int * _sol;
	int _numObjs;
	double _fitness;

public:
	/**
	 * Constructor
	 * @param[in] instance Referencia a un objeto con la información de la instancia del problema MQKP
	 */
	MQKPSolution(MQKPInstance &instance);

	/**
	 * Destructor
	 */
	~MQKPSolution();

	/**
	 * Función que asigna un objeto a la mochila indicada
	 * @param[in] object Índice del objeto a insertar en la mochila indicada
	 * @param[in] knapsack Índice de la mochila donde insertar el objeto
	 */
	void putObjectIn(int object, int knapsack);

	/**
	 * Función que devuelve la mochila en la que está insertado un objeto
	 * @param[in] object Índice del objeto consultado
	 * @return Índice de la mochila en la que está insertado el objeto
	 */
	int whereIsObject(int object);

	/**
	 * Función que devuelve el fitness de la solución
	 *
	 * @return fitness de la solución
	 */
	double getFitness() const;

	/**
	 * Función que asigna el fitness de la solución
	 * @param[in] fitness Fitness de la solución
	 */
	void setFitness(double fitness);

	/**
	 * Función que copia la información de otra solución
	 * @param[in] solution La solución de donde copiar la información
	 */
	void copy(MQKPSolution &solution);
};

#endif
