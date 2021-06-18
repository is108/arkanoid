#include "platform.h"

platform::platform(float x, float y, uint8_t width, uint8_t height, uint8_t platform_speed) : width_ { width }
                                                                                    , height_ { height }
                                                                                    , platform_speed_ { platform_speed }
{   
    shape_.setPosition(x, y);
    shape_.setSize( {float(width_), float(height_)} );
    shape_.setFillColor(Color::Cyan);
    shape_.setOrigin(width_ / 2, height_ / 2);
}

// Обновить местоположение платформы
void platform::update(uint16_t window_width, uint16_t window_height)
{
    shape_.move(speed_);

    // Переместить платформу, в зависимости от того, какая клафиша нажата
    if (Keyboard::isKeyPressed(Keyboard::Key::Left) && left() > 0)
    {
        speed_.x = -platform_speed_;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && right() < window_width)
    {
        speed_.x = platform_speed_;
    }
    else
    {
        speed_.x = 0;
    }
}