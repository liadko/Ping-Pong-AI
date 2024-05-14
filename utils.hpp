#pragma once
#include "headers.hpp"
#include <iomanip>

float len(const v2f& vec);

v2f normalized(const v2f& vec);

float dot(const v2f& v1, const v2f& v2);

void drawVector(const v2f& origin, const v2f& direction, sf::Color color, sf::RenderWindow& window);

void printVec(const vector<float>& vec);

string floatString(float f);

string floatString(float f, int decimals);

float randFloat();
float randFloatCentered();