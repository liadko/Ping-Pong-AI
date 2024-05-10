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
        bool active = true;

        Node() : active(false), input(69.69f) {}
        Node(int id, int layer) : 
            id(id), layer(layer), active(true) {}
    };
    struct Connection {
        int in_node, out_node;
        float weight;
        bool enabled;
    };

    int layer_count;

    int input_count, output_count;

    float initial_connection_percentage;
    int initial_hidden_count;

    int current_node_id = 0;
    static const int MAX_NODES = 30;
    Node nodes[MAX_NODES];

    vector<Connection> connections;

    int* getLayerSizes();
public:
    NeuralNetwork(int input_nodes, int hidden_nodes, int output_nodes);

    void addNode();
    void addConnection();
    void mutate();
    void loadInputs();
    void runNetwork();

    void draw(sf::RenderWindow& window);
};