#pragma once
#pragma once
#include "headers.hpp"

class NeuralNetwork
{
private:

    struct Node {
        int id;
        int layer;
        float input, output;
    };
    struct Connection {
        int in_node, out_node;
        float weight;
        bool enabled;
    };

    int input_count, output_count;

    float initial_connection_percentage;
    int initial_hidden_count;

    vector<Node> nodes;
    vector<Connection> connections;

public:
    NeuralNetwork(int input_nodes, int hidden_nodes, int output_nodes);

    void addNode();
    void addConnection();
    void mutate();
    void loadInputs();
    void runNetwork();

    void draw(sf::RenderWindow& window);
};