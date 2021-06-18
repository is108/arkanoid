#pragma once

#include <vector>
#include <memory>	
#include <unistd.h>

#include "platform.h"
#include "ball.h"
#include "brick.h"

class game
{
public:
    game();
    game(uint16_t window_width, uint16_t window_height);
    
    ~game() = default;

    // Запускает игру
    void run();
private:
    // Устанавливает кирпичи на игровую площадку
    void set_bricks();

    // Начать игру заново
    void start_over();

    uint16_t get_window_width() const;
    uint16_t get_window_height() const;
private:
    uint16_t window_width_ {};
    uint16_t window_height_ {};
    
    uint8_t count_blocks_x {};
    uint8_t count_blocks_y {};

    std::unique_ptr<RenderWindow> window_ {};
    std::shared_ptr<platform> platform_ {};
    std::shared_ptr<ball> ball_ {};
    std::vector<std::shared_ptr<brick> > bricks_ {};
};