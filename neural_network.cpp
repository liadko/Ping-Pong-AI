#include "neural_network.hpp"



NeuralNetwork::NeuralNetwork(int input_nodes, int hidden_nodes, int output_nodes)
    : input_count(input_nodes), output_count(output_nodes), initial_hidden_count(hidden_nodes)
{

    layer_count = 2;

    int layer_index = 0;
    for (int i = 0; i < input_nodes; i++)
    {
        nodes[current_node_id] = Node(current_node_id, layer_index);

        current_node_id++;
    }

    if (hidden_nodes > 0)
    {
        layer_count++;
        layer_index++;
    }
    for (int i = 0; i < hidden_nodes; i++)
    {
        nodes[current_node_id] = Node(current_node_id, layer_index);
        current_node_id++;
    }

    layer_index++;
    for (int i = 0; i < output_nodes; i++)
    {
        nodes[current_node_id] = Node(current_node_id, layer_index);

        current_node_id++;
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
    circle.setFillColor(sf::Color::Transparent);
    circle.setOrigin(circle.getRadius(), circle.getRadius());

    float subsection_size = size.x / layer_count;

    int* layer_sizes = getLayerSizes();
    int* indices_within_layer = new int[layer_count]();


    for (int i = 0; i < MAX_NODES; i++)
    {
        if (!nodes[i].active) continue;

        Node node = nodes[i];

        float x = pos.x + subsection_size * node.layer + subsection_size / 2.0f;


        float layer_box_height = size.y / layer_sizes[node.layer];
        float y = pos.y + layer_box_height * indices_within_layer[node.layer] + layer_box_height / 2.0f;
        indices_within_layer[node.layer]++;



        circle.setPosition(x, y);
        window.draw(circle);
    }


    delete[] layer_sizes;
}

// remember to free the memory after calling this function
int* NeuralNetwork::getLayerSizes()
{
    int* layer_sizes = new int[layer_count]();

    for (int i = 0; i < MAX_NODES; i++)
    {
        if (nodes[i].active)
            layer_sizes[nodes[i].layer]++;
    }

    return layer_sizes;
}