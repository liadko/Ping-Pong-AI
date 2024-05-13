#include "utils.hpp"

float len(const v2f& vec)
{
    if (vec.x == 0 && vec.y == 0) return 0;
    return sqrtf(vec.x * vec.x + vec.y * vec.y);
}

v2f normalized(const v2f& vec)
{
    return vec / len(vec);
}

float dot(const v2f& v1, const v2f& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

void drawVector(const v2f& origin, const v2f& direction, sf::Color color, sf::RenderWindow& window)
{
    if (direction.x == 0 && direction.y == 0) return;

    sf::Vertex line[] =
    { sf::Vertex(origin, sf::Color::White),
    sf::Vertex(origin + normalized(direction) * 30.0f, color)};


    window.draw(line, 2, sf::Lines);
}

void printVec(const vector<float>& vec) {
    // Print opening bracket
    std::cout << "[ ";

    // Iterate over the elements of the vector
    for (size_t i = 0; i < vec.size(); ++i) {
        // Print each element with fixed precision and width
        std::cout << std::fixed << std::setw(7) << std::setprecision(3) << vec[i];

        // Print comma and space if it's not the last element
        if (i < vec.size() - 1) {
            std::cout << ", ";
        }
    }

    // Print closing bracket
    std::cout << " ]" << std::endl;
}

string floatString(float f)
{
    string s = std::to_string(f);
    return s.substr(0, s.find(".") + 3);
}

float randFloat()
{
    return rand() / (float)RAND_MAX;
}