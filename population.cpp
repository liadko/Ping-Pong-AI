#include "population.hpp"


Population::Population(int members)
{
    for (int i = 0; i < members; i++)
        nets.emplace_back(2, 1, 1);
}

bool Population::compareNets(const NeuralNetwork& nn1, const NeuralNetwork& nn2)
{
    return nn1.getFitness() > nn2.getFitness();
}


void Population::progressGeneration()
{

}


void Population::runNets()
{
    vector<vector<float>> inputs =
    {
        {1, 0},
        {0, 1},
        {0, 0},
        {1, 1}
    };
    vector<vector<float>> expected =
    {
        {1},
        {1},
        {0},
        {0}
    };

    //int index = rand() % inputs.size();
    //cout << index << "\n";

    for (NeuralNetwork& net : nets)
    {
        float error = 0;
        for (int i = 0; i < inputs.size(); i++)
        {
            vector<float> result = net.runNetwork(inputs[i]);
            //cout << "Expected: " << expected[i][0] << ". Result: " << result[0] << "\n";
            
            error += abs(result[0] - expected[i][0]);

        }
        cout << "Error: " << error << '\n';
        
        net.setFitness(4 - error);
    }

}