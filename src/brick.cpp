#include "brick.h"

brick::brick(float x, float y, uint8_t block_width, uint8_t block_height) : destroyed_ { false }
                                                                            , strength_ { 2 }
                                                                            , block_width_ { block_width}
                                                                            , block_height_ { block_height }
{
    shape_.setPosition(x, y);
    shape_.setSize({block_width_, block_height_});
    shape_.setFillColor(Color::Red);
    shape_.setOrigin(block_width_ / 2, block_height_ / 2);
}


bool brick::is_destroyed() const
{
    return destroyed_;
}


void brick::set_destroy(bool destroyed)
{
    destroyed_ = destroyed;
}

uint8_t brick::get_strength() const
{
    return strength_;
}

void brick::reduce_strength()
{
    strength_ -= 1;
}
