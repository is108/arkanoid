#pragma once

#include "rectangle.h"

class platform : public rectangle
{
public:
    platform(float x, float y, uint8_t width, uint8_t height, uint8_t platform_speed);
    ~platform() = default;

    // Обновить местоположение платформы
    void update(uint16_t window_width, uint16_t window_height);
private:
    // Скорость платформы
    uint8_t platform_speed_ {};
    
    // Вектор движения платформы
    Vector2f speed_ {};

    // Ширина и высота платформы
    uint8_t width_;
    uint8_t height_; 
};
