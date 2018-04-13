/*
 * MQKPSimulatedAnnealing.h
 *
 * Fichero que define la clase MQKPSimulatedAnnealing. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef INCLUDE_MQKPSIMULATEDANNEALING_H_
#define INCLUDE_MQKPSIMULATEDANNEALING_H_

#include <MQKPSolution.h>
#include <MQKPInstance.h>
#include <MQKPMetaheuristic.h>
#include <MQKPStopCondition.h>
#include <cstdlib>

/**
 * Clase que implementa el Enfriamiento Simulado para el MQKP.
 */
class MQKPSimulatedAnnealing : public MQKPMetaheuristic {

protected:
	/**
	 * Variables miembro
	 * _T almacena la temperatura actual del sistema
	 * _initialProb almacena la probabilidad inicial con la que se aceptan en media los cambios a peores soluciones
	 * _annealingFactor almacena el factor con el que se enfría la temperatura
	 * _solution Solución al MQKP sobre la que trabaja el Enfriamiento Simulado
	 * _instance Instancia del problema que se está abordando
	 */
	double _T;
	double _initialProb;
	double _annealingFactor;
	unsigned _itsPerAnnealing;
	MQKPSolution *_solution;
	MQKPInstance *_instance;

	/**
	 * vector de doubles donde almacena la calidad de la última solución aceptada
	 */
	vector<double> _results;

	/**
	 * Función que indica si se acepta la nueva solución según su diferencia en fitness con respecto a la actual
	 * @param[in] deltaFitness diferencia en fitnees de la nueva solución con respecto a la actual
	 * @return true si se acepta la nueva solución, false en otro caso
	 */
	bool accept(double deltaFitness);

public:
	/**
	 * Constructor
	 */
	MQKPSimulatedAnnealing(){
		_T = 0;
		_initialProb = 0;
		_annealingFactor = 0;
		_itsPerAnnealing = 0;
		_solution = NULL;
		_instance = NULL;
	}

	/**
	 * Destructor
	 */
	virtual ~MQKPSimulatedAnnealing(){

		if (_bestSolution != NULL){
			delete _bestSolution;
			_bestSolution = NULL;
		}
	};


	/**
	 * Función que ejecuta la metaheurística hasta alcanzar la condición de parada
	 * @param[in] stopCondition Condición de parada para la metaheurística
	 */
	virtual void run(MQKPStopCondition &stopCondition);

	/**
	 * Función que asigna la solución inicial para la metaheurística
	 * @param[in] solution Solución inicial a partir de la cual aplicar el enfriamiento simulado
	 */
	void setSolution(MQKPSolution* solution);

	/**
	 * Función que inicializa ciertos parámetros de la metaheurística, en particular, se calcula la temperatura inicial del sistema según la probabilidad con la que se desean aceptar los primeros cambios a peores soluciones
	 * @param[in] initialProb Probabilidad con la que se desean aceptar en media los primeros cambios a peor
	 * @param[in] numInitialEstimates Número de soluciones iniciales sobre las que se estima la temperatura necesaria para aceptar cambios a peores soluciones con la probabilidad indicada
	 * @param[in] annealingFactor Factor con el cual se enfría la temperatura
	 * @param[in] itersPerAnnealing Número de iteraciones entre dos enfriamientos de la temperatura
	 * @param[in] instance Instancia del problema que se va a abordar
	 */
	void initialise(double initialProb, int numInitialEstimates, double annealingFactor, unsigned itsPerAnnealing, MQKPInstance &instance);

	/**
	 * Función que devuelve el vector con los resultados de las soluciones aceptadas, en cada paso, por la búsqueda local
	 *
	 * @return vector con los resultados de las soluciones aceptadas, en cada paso, por la búsqueda local
	 */
	vector<double>& getResults() {
		return _results;
	}
};


#endif /* INCLUDE_MQKPSIMULATEDANNEALING_H_ */
