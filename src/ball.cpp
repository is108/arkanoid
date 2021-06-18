#include "ball.h"

ball::ball(float x, float y, uint8_t radius, uint8_t ball_speed) : radius_ { radius }
                                                                   , ball_speed_ { ball_speed }
{
    speed_.x = 0;
    speed_.y = ball_speed_;

    shape_.setPosition(x, y);
    shape_.setRadius(radius_);
    shape_.setFillColor(Color::Red);
    shape_.setOrigin(radius_, radius_);
}

// Обновить местоположение мяча
void ball::update(uint16_t window_width, uint16_t window_height)
{
    shape_.move(speed_);

    // Проверяем ударился он об стенку и если да, меняем направление мяча
    if(left() < 0)
        speed_.x = ball_speed_;
    else if(right() > window_width)
        speed_.x = -ball_speed_;

    if(top() < 0)
        speed_.y = ball_speed_;
}

// Обновить скорость мяча при попадании в кирпич
void ball::update_speed()
{
    if (abs(speed_.x) == ball_speed_)
        speed_.x *= 1.1;
    if (abs(speed_.y) == ball_speed_)
        speed_.y *= 1.1;
    
    ball_speed_ *= 1.1;
}

// Получить координату x
float ball::get_x() 
{ 
    return shape_.getPosition().x; 
}

// Получить координату y
float ball::get_y() 
{ 
    return shape_.getPosition().y; 
}

// Получить левый край фигуры    
float ball::left() 
{ 
    return get_x() - shape_.getRadius(); 
}

// Получить правый край фигуры    
float ball::right() 
{ 
    return get_x() + shape_.getRadius();
}

// Получить верх фигуры    
float ball::top() 
{ 
    return get_y() - shape_.getRadius(); 
}

// Получить низ фигуры    
float ball::bottom() 
{ 
    return get_y() + shape_.getRadius(); 
}
