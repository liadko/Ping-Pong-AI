#include "neural_network.hpp"



NeuralNetwork::NeuralNetwork(int input_nodes, int hidden_nodes, int output_nodes)
    : input_count(input_nodes), output_count(output_nodes), initial_hidden_count(hidden_nodes)
{

    layer_count = 3;

    for (int i = 0; i < input_nodes; i++)
    {
        nodes.emplace_back(nodes.size(), 0);
    }
    for (int i = 0; i < output_nodes; i++)
    {
        nodes.emplace_back(nodes.size(), 2);
    }

    for (int i = 0; i < hidden_nodes; i++)
    {
        nodes.emplace_back(nodes.size(), 1);
    }

    // connections
    for (int hidden_i = input_nodes + output_nodes; hidden_i < nodes.size(); hidden_i++)
    {
        // from input to hidden
        for (int input_i = 0; input_i < input_nodes; input_i++)
            addConnection(input_i, hidden_i);

        // from hidden to output
        for (int output_i = 0; output_i < output_nodes; output_i++)
            addConnection(hidden_i, input_nodes + output_i);
    }


}


void NeuralNetwork::draw(sf::RenderWindow& window)
{
    v2f pos = { 0, 0 };
    v2f size = { 800, 500 };

    sf::RectangleShape outline(size);
    outline.setOutlineThickness(2);
    outline.setOutlineColor(sf::Color::Green);
    outline.setFillColor(sf::Color::Transparent);
    window.draw(outline);

    sf::CircleShape circle(30);
    circle.setOutlineColor(sf::Color::White);
    circle.setOutlineThickness(2);
    circle.setFillColor(sf::Color::Black);
    circle.setOrigin(circle.getRadius(), circle.getRadius());

    float subsection_size = size.x / layer_count;

    int* layer_sizes = getLayerSizes();
    int* indices_within_layer = new int[layer_count]();


    for (Node& node : nodes)
    {
        if (!node.active) continue;

        node.pos_x = pos.x + subsection_size * node.layer + subsection_size / 2.0f;


        float layer_box_height = size.y / layer_sizes[node.layer];
        node.pos_y = pos.y + layer_box_height * indices_within_layer[node.layer] + layer_box_height / 2.0f;
        indices_within_layer[node.layer]++;

    }

    delete[] layer_sizes;
    delete[] indices_within_layer;

    for (const Connection& con : connections)
    {
        if (!con.enabled) continue;


        Node& in = nodes[con.in_node];
        Node& out = nodes[con.out_node];


        sf::Vertex line[] = { 
            sf::Vertex({in.pos_x, in.pos_y}, sf::Color::Green),
            sf::Vertex({out.pos_x, out.pos_y}, sf::Color::Green),
        };

        window.draw(line, 2, sf::Lines);
    }

    for (Node& node : nodes)
    {
        if (!node.active) continue;

        circle.setPosition(node.pos_x, node.pos_y);
        window.draw(circle);
    }
}

void NeuralNetwork::addConnection(int in, int out)
{
    Node& out_node = getNode(out);
    out_node.incoming_connection_count++;

    connections.emplace_back(in, out);
}

// remember to free the memory after calling this function
int* NeuralNetwork::getLayerSizes()
{
    int* layer_sizes = new int[layer_count]();

    for (const Node& node : nodes)
    {
        if (!node.active) continue;

        layer_sizes[node.layer]++;
    }

    return layer_sizes;
}

NeuralNetwork::Node& NeuralNetwork::getNode(int node_id)
{
    if (node_id < 0 || node_id >= nodes.size()) throw std::out_of_range("No Node with id: " + std::to_string(node_id));

    return nodes[node_id];
}