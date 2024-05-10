#include "neural_network.hpp"

NeuralNetwork::NeuralNetwork(int input_nodes, int hidden_nodes, int output_nodes)
    : input_count(input_nodes), output_count(output_nodes), initial_hidden_count(hidden_nodes)
{
    for (int i = 0; i < input_nodes; i++)
    {
        Node new_node = { i, 0, -1, -1 };
        nodes.push_back(new_node);
    }
    for (int i = 0; i < output_nodes; i++)
    {
        Node new_node = { input_nodes + i, 1, -1, -1 };
        nodes.push_back(new_node);
    }


}
