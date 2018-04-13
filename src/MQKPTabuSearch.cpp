/*
 * MQKPTabuSearch.cpp
 *
 * Fichero que define las funciones de la clase MQKPTabuSearch. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#include <MQKPEvaluator.h>
#include <MQKPObjectAssignmentOperation.h>
#include <MQKPTabuSearch.h>
#include <initializer_list>
#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>

using namespace std;

void MQKPTabuSearch::initialise(MQKPInstance* instance, unsigned tabuTennure) {
	_instance = instance;
	_tabuTennure = tabuTennure;
}

void MQKPTabuSearch::setSolution(MQKPSolution* solution) {

	if (_solution != NULL){
		cerr << "No se debe invocar más de una vez el método MQKPTabuSearch::setSolution" << endl;
		exit(1);
	}

	this->_solution = solution;

	if (_bestSolution == NULL) {
		_bestSolution = new MQKPSolution(*_instance);
	}

	_bestSolution->copy(*solution);
}

void MQKPTabuSearch::run(MQKPStopCondition& stopCondition) {
	if (_solution == NULL) {
		cerr << "Tabu search has not been given an initial solution" << endl;
		exit(-1);
	}

	_results.clear();
	unsigned numObjs = _instance->getNumObjs();
	unsigned numKnapsacks = _instance->getNumKnapsacks();
	unsigned numIterations = 0;

	/**
	 * TODO
	 * Mientras no se alcance la condición de parada
	 *  1. Generar una permutación de objetos
	 *  2. Buscar la mejor operación no tabú de asignación de un objeto a una mochila (incluida la 0)
	 *  3. Aplicar la operación
	 *  4. Insertar el índice del objeto afectado en la memoria tabú
	 *  5. Actualizar la mejor solución hasta el momento
	 */

	while (!stopCondition.reached()) {

		vector<int> perm;
		MQKPInstance::randomPermutation(numObjs, perm);
		double bestDeltaFitness = 0;
		bool initialisedDeltaFitness = false;
		MQKPObjectAssignmentOperation bestOperation;

		//Buscar la mejor operación no tabú
		for (unsigned i = 0; i < numObjs; i++) {
			unsigned indexObj = perm[i];

			//Si el objeto no es tabú (utilizar _shortTermMem_aux.find)
			if (_shortTermMem_aux.end()==_shortTermMem_aux.find(indexObj)) {

				//Probar todas las mochilas (incluida la 0) y elegir la mejor opción
				for (unsigned j=0;j<=numKnapsacks;j++) {

					//Saltarse el cambio que no hace nada
					if (_solution->whereIsObject(indexObj) == ((int)j))
						continue;

					//Obtener la diferencia de fitness de aplicar dicha operación
					double deltaFitness = MQKPEvaluator::computeDeltaFitness(*_instance,*_solution,indexObj,(int)j);

					//Si la diferencia de fitness es la mejor hasta el momento, apuntarla para aplicarla después
					if (deltaFitness > bestDeltaFitness or initialisedDeltaFitness == false) {
						initialisedDeltaFitness = true;
						bestDeltaFitness = deltaFitness;
						bestOperation.setValues(indexObj,j,bestDeltaFitness);
					}
				}
			}
		}

		//TODO Aplicar la operación y almacenarla en la memoria a corto plazo
		bestOperation.apply(*_solution);
		_shortTermMem.push(bestOperation.getObj());

		_shortTermMem_aux.insert(bestOperation.getObj());

		//TODO Si hay demasiados elementos en la memoria, según la tenencia tabú, eliminar el más antiguo
		if (_shortTermMem.size() > _tabuTennure) {
			unsigned value = _shortTermMem.front();
			_shortTermMem.pop();
			_shortTermMem_aux.erase(value);
		}

		//Actualizar la mejor solución
		if (MQKPEvaluator::compare(_solution->getFitness(),_bestSolution->getFitness()) > 0) {
			_bestSolution->copy(*_solution);
		}

		numIterations++;
		_results.push_back(_solution->getFitness());

		stopCondition.notifyIteration();
	}
}
