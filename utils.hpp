#pragma once
#include "headers.hpp"

float len(const v2f& vec);

v2f normalized(const v2f& vec);

float dot(const v2f& v1, const v2f& v2);

void drawVector(const v2f& origin, const v2f& direction, sf::RenderWindow& window);