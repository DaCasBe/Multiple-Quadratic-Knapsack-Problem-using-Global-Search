/*
 * MQKPGrasp.cpp
 *
 * Fichero que define las funciones de la clase MQKPGrasp. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#include <MQKPGrasp.h>
#include <vector>
#include <MQKPSimpleFirstImprovementNO.h>
#include <MQKPLocalSearch.h>
#include <iostream>

using namespace std;

void MQKPGrasp::chooseOperation(MQKPObjectAssignmentOperation& operation) {

	int bestObj = 0;
	int bestKnapsack = 0;
	double bestDensity = 0;
	double bestDeltaFitness = 0;
	bool initialisedBestDensity = false;
	unsigned numObjs = _instance->getNumObjs();
	unsigned numKnapsacks = _instance->getNumKnapsacks();

	/**
	 * Calcular el número de intentos como el porcentaje _alpha por el número de posibilidades, que es el número de objetos por el número de mochilas.
	 *
	 * En este paso no se considerará que ya haya objetos asignados a alguna mochila, la mochila 0 que representa objetos sin asignar a ninguna mochila, ni que haya mochilas ya completamente llenas
	 */
	unsigned numTries = ((unsigned)(numObjs * numKnapsacks * _alpha));

	/**
	 * TODO
	 * Generar alternativas de objeto y mochila aleatorias (no se considera la mochila 0) y quedarse con la alterantiva de mejor densidad
	 */
	for (unsigned i = 0; i < numTries; i++) {
		int indexObj = rand()%numObjs; //Se elige un objeto aleatorio
		int indexKnapsack = (rand()%numKnapsacks)+1; //Se elige una mochila aleatoria

		double deltaFitness = MQKPEvaluator::computeDeltaFitness(*_instance,*_sol,indexObj,indexKnapsack); //TODO obtener la mejora en fitness de dicha operación
		double density = deltaFitness/_instance->getWeight(indexObj);//TODO calcular la densidad de dicha operación como la diferencia en fitness dividido por el peso del objeto

		//TODO actualizar si resulta ser la mejor
		if (density > bestDensity || initialisedBestDensity == false) {
			initialisedBestDensity = true;
			bestDensity = density;
			bestObj = indexObj;
			bestKnapsack = indexKnapsack;
			bestDeltaFitness = deltaFitness;
		}
	}

	operation.setValues(bestObj, bestKnapsack,
			bestDeltaFitness);
}

void MQKPGrasp::buildInitialSolution() {

	/**
	 * TODO
	 * Vaciar la solución _sol asignándole un fitness de 0 y poniendo todos los objetos en la mochila 0
	 */
	unsigned numObjs = _instance->getNumObjs();

	_sol->setFitness(0);		//Se asigna un 0 al fitness
	for (unsigned i = 0; i < numObjs; i++) {
		_sol->putObjectIn(i,0);	//Se ponen todos los objetos de la mochila a 0
	}

	/** Seleccionar la primera operación */
	MQKPObjectAssignmentOperation operation;
	chooseOperation(operation);

	/**
	 * TODO
	 * Mientras la operación tenga un incremento de fitness positivo, operation.getDeltaFitness(),
	 *  1. aplicar la operación en _sol
	 *  2. Almacenar el fitness de la solución en _result (para las gráficas)
	 *  3. seleccionar una nueva operación
	 */
	while (operation.getDeltaFitness() > 0) {
		operation.apply(*_sol);						//aplicar la operación en _sol
		_results.push_back(_sol->getFitness());		//Almacenar el fitness de la solución
		chooseOperation(operation);					//seleccionar una nueva operación
	}
}

void MQKPGrasp::initialise(double alpha, MQKPInstance& instance) {

	_sol = new MQKPSolution(instance);
	_bestSolution = new MQKPSolution(instance);
	_bestSolution->copy(*_sol);
	_instance = &instance;
	_alpha = alpha;
}

void MQKPGrasp::run(MQKPStopCondition& stopCondition) {

	if (_sol == NULL) {
		cerr << "GRASP was not initialised" << endl;
		exit(-1);
	}

	/**
	 * TODO
	 * Mientras no se alcance el criterio de parada
	 *   1. Generar una solución inicial invocando al método correspondiente
	 *   2. Almacenar el fitness de la solución en _results
	 *   3. Optimizar _sol con la búsqueda local y el operador de vecindario de la metaheurística
	 *   4. Actualizar la mejor solución
	 */
	while (!stopCondition.reached()) { //No se alcanza el criterio de parada
		buildInitialSolution(); //Se genera una solucion inicial
		_results.push_back(_sol->getFitness()); //Se almacena el fitness actual
		_ls.optimise(*_instance,_no,*_sol); //Se optimiza la solucion

		vector<double> &auxResults = _ls.getResults();

		for (auto result : auxResults){
			_results.push_back(result);
		}

		if (MQKPEvaluator::compare(_sol->getFitness(), _bestSolution->getFitness()) > 0)
			_bestSolution->copy(*_sol);

			stopCondition.notifyIteration();
	}
}
