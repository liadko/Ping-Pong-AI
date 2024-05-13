#include "neural_network.hpp"
#include "utils.hpp"


NeuralNetwork::NeuralNetwork(int input_nodes, int hidden_nodes, int output_nodes)
    : input_count(input_nodes), output_count(output_nodes), initial_hidden_count(hidden_nodes)
{

    // Bias node
    nodes.emplace_back(nodes.size());

    nodes[0].output = 1; // Bias Node

    for (int i = 0; i < input_nodes; i++)
    {
        nodes.emplace_back(nodes.size());
    }
    for (int i = 0; i < output_nodes; i++)
    {
        nodes.emplace_back(nodes.size());
    }

    for (int i = 0; i < hidden_nodes; i++)
    {
        nodes.emplace_back(nodes.size());
    }

    // connections
    for (int hidden_i = 1 + input_nodes + output_nodes; hidden_i < nodes.size(); hidden_i++)
    {

        // from hidden to output
        for (int output_i = 0; output_i < output_nodes; output_i++)
            addConnection(hidden_i, 1 + input_nodes + output_i);

    }

    // from inputs to all
    for (int input_i = 1; input_i < input_nodes + 1; input_i++)
        for(int other = input_nodes + 1; other < nodes.size(); other++)
            addConnection(input_i, other);

    // from bias to all
    for (int i = input_count + 1; i < nodes.size(); i++)
        addConnection(0, i);

    orderLayers();

    initWeights();


    initFonts();
}

void NeuralNetwork::initFonts()
{
    bold_font.loadFromFile("fonts/Montserrat-Bold.ttf");
    regular_font.loadFromFile("fonts/Montserrat-Regular.ttf");
}

void NeuralNetwork::initWeights()
{
    for (Connection& connection : connections)
        connection.weight = (2 * randFloat() - 1) * 0.1f;
}
void NeuralNetwork::orderLayers()
{

    int node_count = nodes.size();
    int* layer_info = new int[node_count];
    for (int i = 0; i < node_count; i++)
    {
        layer_info[i] = -1;
        nodes[i].layer = -1;

        nodes[i].temp_connection_count = nodes[i].incoming_connection_count;
    }

    for (int i = 0; i < connections.size(); i++)
    {
        connections[i].traversed = false;
    }

    int current_layer = 0;

    //mark bias node and input layer nodes as layer 0
    for (int i = 0; i < input_count + 1; i++)
        layer_info[i] = 0;

    while (true)
    {

        bool all_connections_traversed = true;
        // delete all connections to current layer
        for (Connection& connection : connections)
        {
            if (connection.traversed) continue;

            all_connections_traversed = false;

            if (layer_info[connection.in_node_id] == current_layer)
            {
                // "delete" connection
                connection.traversed = true;
                Node& out_node = getNode(connection.out_node_id);
                out_node.temp_connection_count--;

                // maybe add out_node to next layer
                if (out_node.temp_connection_count == 0)
                    layer_info[out_node.id] = current_layer + 1;
            }
        }

        current_layer++;

        if (all_connections_traversed)
            break;
    }

    layer_count = current_layer;

    for (int i = 0; i < node_count; i++)
    {
        nodes[i].layer = layer_info[i];
    }

    delete[] layer_info;


    updateLayerSizes();
}

void NeuralNetwork::loadInputs(const vector<float>& inputs)
{
    if (inputs.size() != input_count)
    {
        cerr << "\nERROR:\ninput layer size: " + std::to_string(input_count) +
            ". inputs.size():" + std::to_string(inputs.size()) << '\n';
        return;
    }

    for (int i = 0; i < input_count; i++)
    {
        nodes[i + 1].output = inputs[i]; // straight to the node's output
    }
}

vector<float> NeuralNetwork::runNetwork(const vector<float>& inputs)
{
    loadInputs(inputs);

    // reset inputs
    for (Node& node : nodes)
    {
        node.input = 0;
    }

    // run through layers
    for (int layer = 1; layer < layer_count; layer++)
    {
        for (Connection& connection : connections)
        {
            Node& in_node = getNode(connection.in_node_id);
            if (in_node.layer == layer - 1)
                getNode(connection.out_node_id).input += in_node.output * connection.weight;
        }

        for (Node& node : nodes)
        {
            if (node.layer == layer)
                node.output = activationFunction(node.input);
        }
    }


    // compile output vector
    vector<float> output(layer_sizes[layer_count - 1]);

    int i = 0;
    for (const Node& node : nodes)
    {
        if (node.layer == layer_count - 1)
        {
            output[i] = node.output;
            i++;
        }
    }

    return output;
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

    float node_radius = size.y / 17.0f;

    sf::CircleShape circle(node_radius);
    circle.setOutlineColor(sf::Color::White);
    circle.setOutlineThickness(2);
    circle.setFillColor(sf::Color::Black);
    circle.setOrigin(circle.getRadius(), circle.getRadius());

    float subsection_size = size.x / layer_count;


    int* indices_within_layer = new int[layer_count]();


    for (Node& node : nodes)
    {
        if (!node.active) continue;

        node.pos_x = pos.x + subsection_size * node.layer + subsection_size / 2.0f;

        if (node.id == 0) // bias node
        {
            node.pos_y = node_radius * 1.5f;
            continue;
        }

        float layer_box_height = size.y / layer_sizes[node.layer];
        node.pos_y = pos.y + layer_box_height * indices_within_layer[node.layer] + layer_box_height / 2.0f;
        indices_within_layer[node.layer]++;

    }

    delete[] indices_within_layer;

    sf::Text detail_text("DETAIL", regular_font, 14);
    detail_text.setOutlineThickness(5);
    detail_text.setOutlineColor(sf::Color::Black);

    for (const Connection& con : connections)
    {
        if (!con.enabled) continue;


        Node& in = nodes[con.in_node_id];
        Node& out = nodes[con.out_node_id];

        
        sf::Vertex line[] = {
            sf::Vertex({in.pos_x, in.pos_y}, sf::Color::Green),
            sf::Vertex({out.pos_x, out.pos_y}, sf::Color::Green),
        };

        window.draw(line, 2, sf::Lines);



        detail_text.setString(floatString(con.weight));
        detail_text.setOrigin(detail_text.getLocalBounds().width / 2.0f, detail_text.getLocalBounds().height / 2.0f);
        detail_text.setPosition((in.pos_x + out.pos_x) / 2, (in.pos_y + out.pos_y) / 2);
        window.draw(detail_text);
    }

    for (Node& node : nodes)
    {
        if (!node.active) continue;

        // node circle
        circle.setPosition(node.pos_x, node.pos_y);
        window.draw(circle);

        // node id
        sf::Text id_text(std::to_string(node.id), bold_font, 26);
        id_text.setOrigin(id_text.getLocalBounds().width / 2.0f, id_text.getLocalBounds().height / 1.2f);
        id_text.setPosition(node.pos_x, node.pos_y);
        window.draw(id_text);

        // input, output
        detail_text.setString(floatString(node.input));
        detail_text.setOrigin(detail_text.getLocalBounds().width / 2.0f, detail_text.getLocalBounds().height / 2.0f);
        detail_text.setPosition(node.pos_x - node_radius * 2 + 5, node.pos_y);
        window.draw(detail_text);

        detail_text.setString(floatString(node.output));
        detail_text.setOrigin(detail_text.getLocalBounds().width / 2.0f, detail_text.getLocalBounds().height / 2.0f);
        detail_text.setPosition(node.pos_x + node_radius * 2 + 1, node.pos_y);
        window.draw(detail_text);
    }


    sf::Text description("Fitness: " + , regular_font, 14);

}

void NeuralNetwork::addConnection(int in, int out)
{
    Node& out_node = getNode(out);
    out_node.incoming_connection_count++;

    connections.emplace_back(in, out);
}

void NeuralNetwork::updateLayerSizes()
{
    layer_sizes.resize(layer_count);

    for (const Node& node : nodes)
    {
        if (!node.active || node.id == 0) continue;

        layer_sizes[node.layer]++;
    }

}


NeuralNetwork::Node& NeuralNetwork::getNode(int node_id)
{
    if (node_id < 0 || node_id >= nodes.size()) throw std::out_of_range("No Node with id: " + std::to_string(node_id));

    return nodes[node_id];
}

float NeuralNetwork::activationFunction(float x)
{
    return  1.0f / (1 + expf(-x));
}