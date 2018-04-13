/*
 * MQKPIteratedGreedy.h
 *
 * Fichero que define la clase MQKPIteratedGreedy. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef INCLUDE_MQKPITERATEDGREEDY_H_
#define INCLUDE_MQKPITERATEDGREEDY_H_

#include <MQKPMetaheuristic.h>
#include <MQKPSolution.h>
#include <MQKPObjectAssignmentOperation.h>

/**
 * Clase que implementa la metaheurística Iterated Greedy para el MQKP, en la variante en la que la destrucción se aplica siempre sobre la mejor solución y no se aplica búsqueda local
 */
class MQKPIteratedGreedy : public MQKPMetaheuristic{
protected:

	/**
	 * Variables miembro de la clase
	 * _alpha guarda la probabilidad con que los objetos se sacan de sus mochilas correspondientes.
	 * _instance tiene un puntero a la instancia del problema abordada
	 * _sol tiene la solución sobre la que trabaja Iterated Greedy durante las destrucciones y construcciones
	 */
	double _alpha;
	MQKPInstance *_instance;
	MQKPSolution *_sol;

	/**
	 * vector de doubles donde almacena la calidad de la última solución aceptada
	 */
	vector<double> _results;

	/**
	 * Función que devuelve la mejor operación de asignación de un objeto sin asignar a una mochila
	 * @param[out] operation Operación de asignación de un objeto a mochila seleccionada
	 */
	void chooseOperation(MQKPObjectAssignmentOperation &operation);

	/**
	 * Función que reconstruye la solución _sol. Para ello, invoca repetidamente a la función chooseOperation hasta que no encuentra ninguna otra operación de asignación que mejore la solución actual.
	 * Los cambios se van almacenando en la variable miembro _sol.
	 */
	void rebuild();

	/**
	 * Función que destruye parcialmente la solución _sol. Para ello, saca objetos de sus mochilas correspondientes con probabilidad _alpha
	 */
	void destroy();

public:
	/**
	 * Constructor
	 */
	MQKPIteratedGreedy(){
		_alpha = 0.;
		_instance = NULL;
		_sol = NULL;
	}

	/**
	 * Destructor
	 */
	virtual ~MQKPIteratedGreedy(){

		if (_bestSolution != NULL){
			delete _bestSolution;
			_bestSolution = NULL;
		}

		if (_sol != NULL){
			delete _sol;
			_sol = NULL;
		}
	}

	/**
	 * Función que inicializa ciertos parámetros de la metaheurística.
	 * En particular, las variables miembro _sol y _bestSolution y la probabilidad alpha
	 * @param[in] alpha Probabilidad entre 0 y 1 de sacar objetos de sus mochilas en la fase de destrucción
	 * @param[in] instance Instancia del problema que se va a abordar
	 */
	void initialise(double alpha, MQKPInstance &instance);

	/**
	 * Función que ejecuta la metaheurística hasta alcanzar la condición de parada
	 * @param[in] stopCondition Condición de parada para la metaheurística
	 */
	virtual void run(MQKPStopCondition &stopCondition);

	/**
	 * Función que devuelve el vector con los resultados de las soluciones aceptadas, en cada paso, por la búsqueda local
	 *
	 * @return vector con los resultados de las soluciones aceptadas, en cada paso, por la búsqueda local
	 */
	vector<double>& getResults() {
		return _results;
	}
};



#endif /* INCLUDE_MQKPITERATEDGREEDY_H_ */
