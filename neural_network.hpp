#pragma once
#pragma once
#include "headers.hpp"

class NeuralNetwork
{
private:

    struct Node {
        bool active;
        
        int id;
        int layer = -1;
        float input = -1.0f, output = -1.0f;

        // for layer ordering
        int incoming_connection_count = 0;
        int temp_connection_count = -1;

        // for drawing
        float pos_x = 0, pos_y = 0;

        // default ctor
        Node() : 
            active(false), input(69.69f) {}
        
        // useful ctor
        Node(int id) : 
            id(id), active(true) {}
    };


    struct Connection {
        bool enabled = true;

        int in_node_id, out_node_id;
        float weight = 1; 

        // for layer ordering
        bool traversed = false;

        Connection(int in, int out) :
            in_node_id(in), out_node_id(out) {}
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

    void orderLayers();

    void addNode();
    void addConnection(int in, int out);
    void mutate();
    void loadInputs(const vector<float>& inputs);
    void runNetwork();
    void updateLayers(); // each node 

    void draw(sf::RenderWindow& window);
};