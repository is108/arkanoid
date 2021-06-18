#include "rectangle.h"

// Получить координату x
float rectangle::get_x() 
{
    return shape_.getPosition().x; 
}

// Получить координату y
float rectangle::get_y() 
{
    return shape_.getPosition().y; 
}

// Получить левый край фигуры
float rectangle::left() 
{
    return get_x() - shape_.getSize().x / 2; 
}

// Получить правый край фигуры
float rectangle::right() 
{ 
    return get_x() + shape_.getSize().x / 2; 
}

// Получить верх фигуры
float rectangle::top() 
{ 
    return get_y() - shape_.getSize().y / 2; 
}

// Получить низ фигуры
float rectangle::bottom() 
{ 
    return get_y() + shape_.getSize().y / 2; 
}