#pragma once
#include "headers.hpp"
#include "neural_network.hpp"
//#include "simulation.hpp"

class Population
{
private:
    vector<NeuralNetwork> nets;

    bool compareNets(const NeuralNetwork& nn1, const NeuralNetwork& nn2);

public:
    Population(int members);

    void progressGeneration();

    void runNets();

    NeuralNetwork& getNet() { return nets[0]; };
};
