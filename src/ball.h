#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

class ball 
{
public:
    ball(float x, float y, uint8_t radius, uint8_t ball_speed);

    // Обновить местоположение мяча
    void update(uint16_t window_width, uint16_t window_height);

    // Обновить скорость мяча при попадании в кирпич
    void update_speed();

    // Получить координату x
    float get_x();

    // Получить координату y
    float get_y();

    // Получить левый край фигуры    
    float left();

    // Получить правый край фигуры
    float right();

    // Получить низ фигуры
    float bottom();

    // Получить верх фигуры
    float top();

public:
    CircleShape shape_ {};

    // Скорость мяча
    float ball_speed_ {};
    
    // Вектор движения мяча
    Vector2f speed_ = {};
    
    uint8_t radius_ {};
};