#pragma once

#include "rectangle.h"

class brick : public rectangle
{
public:
    brick(float x, float y, uint8_t block_width, uint8_t block_height);
    ~brick() = default;

    bool is_destroyed() const;
    void set_destroy(bool destroyed);

    uint8_t get_strength() const;
    void reduce_strength();
private:
    // Размеры блока
    uint8_t block_height_ {};
    uint8_t block_width_ {};

    // Разрушен ли кирпич
    bool destroyed_ {};
    
    // Прочность кирпича
    uint8_t strength_ {};
};