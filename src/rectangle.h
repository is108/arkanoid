#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

class rectangle
{
public:
    rectangle() = default;
    ~rectangle() = default;

    // Получить координату x
    float get_x();
    
    // Получить координату y
    float get_y();

    // Получить левый край фигуры
    float left();

    // Получить правый край фигуры
    float right();

    // Получить верх фигуры
    float top();

    // Получить низ фигуры
    float bottom();
    
public:
    RectangleShape shape_ {};
};