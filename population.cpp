#include "population.hpp"
#include "utils.hpp"

Population::Population()
{
    for (int i = 0; i < population_size; i++)
        nets.emplace_back(input, hidden, output);
}

bool Population::compareNets(const NeuralNetwork& nn1, const NeuralNetwork& nn2)
{
    return nn1.getFitness() > nn2.getFitness();
}


void Population::progressGeneration()
{
    // evaluation
    runNets(); 

    std::sort(nets.begin(), nets.end(), Population::compareNets);

    // selection
    vector<NeuralNetwork> next_gen;

    for (int i = 0; i < population_size * elitism_percentage; i++)
        next_gen.push_back(nets[i]);
    for (int i = 0; i < population_size * dumbass_percentage; i++)
        nets.emplace_back(input, hidden, output);

    while (next_gen.size() < population_size)
    {
        int net_index = getRandomNetIndex();

        next_gen.push_back(nets[net_index]);
        next_gen[next_gen.size() - 1].mutate(); // mutation

    }

    nets = next_gen;
}

int Population::getRandomNetIndex()
{
    float fitness_sum = 0;
    for (int i = 0; i < nets.size(); i++)
        fitness_sum += nets[i].getFitness();

    float r = randFloat();
    float current_prob = 0;
    for (int i = nets.size() - 1; i >= 0; i--)
    {
        current_prob += nets[i].getFitness() / fitness_sum;
        if (r < current_prob)
            return i;
    }

    throw new std::runtime_error("couldn't select random net");
}

// returns if one net got the solution
bool Population::runNets()
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
    float someone_got_it = false;

    for (NeuralNetwork& net : nets)
    {
        float facts = true;
        float errors = 0;
        for (int i = 0; i < inputs.size(); i++)
        {
            vector<float> result = net.runNetwork(inputs[i]);
            //cout << "Expected: " << expected[i][0] << ". Result: " << result[0] << "\n";
            

            float error = abs(result[0] - expected[i][0]);
            if (round(result[0]) != expected[i][0])
                facts = false;
            errors += error * error;
        }
        //cout << "Error: " << error << '\n';
        
        net.setFitness(4 - errors);

        if (facts) someone_got_it = true;
    }

    return someone_got_it;
}