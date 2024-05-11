#pragma once
#pragma once
#include "headers.hpp"

class NeuralNetwork
{
private:

    struct Node {
        bool active;
        
        int id;
        int layer;
        float input = -1.0f, output = -1.0f;

        int incoming_connection_count = 0;

        // for drawing
        float pos_x = 0, pos_y = 0;

        // default ctor
        Node() : 
            active(false), input(69.69f) {}
        
        // useful ctor
        Node(int id, int layer) : 
            id(id), layer(layer), active(true) {}
    };
    struct Connection {
        bool enabled = true;

        int in_node, out_node;
        float weight = 1; 

        
        Connection(int in, int out) :
            in_node(in), out_node(out) {}
    };

    int layer_count;

    int input_count, output_count;

    float initial_connection_percentage;
    int initial_hidden_count;


    vector<Node> nodes;
    vector<Connection> connections;

    int* getLayerSizes();
    Node& getNode(int node_id);

public:
    NeuralNetwork(int input_nodes, int hidden_nodes, int output_nodes);

    void addNode();
    void addConnection(int in, int out);
    void mutate();
    void loadInputs(vector<float> inputs);
    void runNetwork();
    void updateLayers(); // each node 

    void draw(sf::RenderWindow& window);
};