#pragma once
#include "headers.hpp"
#include "neural_network.hpp"
//#include "simulation.hpp"

class Population
{
private:
    vector<NeuralNetwork> nets;

    int population_size = 150;
    
    float elitism_percentage = 0.15; // percent of top nets that get copied directly to next gen
    float dumbass_percentage = 0.05; // percent of next gen nets that are entirley random

    int input = 2, hidden = 1, output = 1;

    static bool compareNets(const NeuralNetwork& nn1, const NeuralNetwork& nn2);
    int getRandomNetIndex();

public:
    Population();

    void progressGeneration();

    bool runNets();

    NeuralNetwork& getNet() { return nets[0]; };
};
