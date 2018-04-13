/*
 * MQKPLocalSearch.cpp
 *
 * Fichero que define las funciones de la clase MQKPLocalSearch. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#include <MQKPLocalSearch.h>
#include <MQKPInstance.h>
#include <MQKPSolution.h>
#include <MQKPNeighExplorer.h>
#include <MQKPObjectAssignmentOperation.h>

MQKPLocalSearch::MQKPLocalSearch() {
}

MQKPLocalSearch::~MQKPLocalSearch() {
}

void MQKPLocalSearch::optimise(MQKPInstance& instance,
		MQKPNeighExplorer& explorer, MQKPSolution& solution) {

	_results.clear();
	_results.push_back(solution.getFitness());
	MQKPObjectAssignmentOperation operation;

	/**
	 * 1. Aplica una vez la exploración del vecindario y almacena si se ha conseguido o no mejorar la solución
	 *
	 * 2. Mientras se haya conseguido mejorar la solución
	 *   a. Aplica el cambio indicado en la exploración anterior
	 *   b. Almacena en _results el nuevo fitness de la solución
	 *   c. Aplica una nueva exploración del vecindario
	 */

	bool gotBetter = explorer.findOperation(instance, solution, operation);

	while (gotBetter) {
		operation.apply(solution);
		_results.push_back(solution.getFitness());
		gotBetter = explorer.findOperation(instance, solution, operation);
	}
}
