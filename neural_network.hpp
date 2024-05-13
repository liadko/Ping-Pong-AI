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

    int input_count, output_count;

    int layer_count;
    vector<int> layer_sizes;

    //float initial_connection_percentage;
    int initial_hidden_count;


    vector<Node> nodes;
    vector<Connection> connections;
    // for drawing
    sf::Font bold_font, regular_font;

    // for drawing
    void initFonts();

    // for running
    float fitness;


    // layers
    void updateLayerSizes();
    void orderLayers();

    void loadInputs(const vector<float>& inputs);
    void initWeights();
    Node& getNode(int node_id);


    float activationFunction(float x);

public:
    // set up
    NeuralNetwork(int input_nodes, int hidden_nodes, int output_nodes);
    

    // mutations
    void addNode(); // remember to call orderLayers after doing this
    void addConnection(int in, int out); // remember to call orderLayers after doing this
    void mutate();

    // running
    vector<float> runNetwork(const vector<float>& inputs);
    float getFitness() const { return fitness; };
    void setFitness(float fitness) { this->fitness = fitness; };

    // drawing
    void draw(sf::RenderWindow& window);
};