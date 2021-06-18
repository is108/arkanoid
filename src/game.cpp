#include "game.h"
#include "utils.h"

constexpr auto MIN_WINDOW_WIDTH = 500;
constexpr auto MIN_WINDOW_HEIGHT = 400;

constexpr auto EDGE_INDENT = 25;
constexpr auto INDENT_BETWEEN_BRICKS = 5;

constexpr uint8_t BLOCK_WIDTH = 60;
constexpr uint8_t BLOCK_HEIGHT = 20;

constexpr uint8_t PLATFORM_WIDTH = 200;
constexpr uint8_t PLATFORM_HEIGHT = 20;
constexpr uint8_t PLATFORM_SPEED = 6;

constexpr uint8_t BALL_RADIUS = 11;
constexpr float BALL_SPEED = 1.f;

game::game()
{
    // Устанавливаем стандартные размеры окна
    window_width_ = 1000;
    window_height_ = 600;

    // Рассчитываем размер занимаемый кирпичами по оси X, по оси Y устанавливается по умолчанию
    count_blocks_x = ((window_width_ - EDGE_INDENT * 2) - ((window_width_ - EDGE_INDENT * 2) / BLOCK_WIDTH) * INDENT_BETWEEN_BRICKS) / BLOCK_WIDTH;
    count_blocks_y = 7;

    window_ = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(window_width_, window_height_), "Arkanoid"));
    platform_ = std::make_shared<platform>(window_width_ / 2, window_height_ - 50, PLATFORM_WIDTH, PLATFORM_HEIGHT, PLATFORM_SPEED);
    ball_ = std::make_shared<ball>(window_width_ / 2, window_height_ / 2, BALL_RADIUS, BALL_SPEED);
    
    // Ограничиваем частоту кадров
    window_->setFramerateLimit(250);

    set_bricks();
}


game::game(uint16_t window_width, uint16_t window_height)
{
    // Если задаваемая ширина окна меньше минимальной, устанавливаем минимальную
    if (window_width < MIN_WINDOW_WIDTH)
    {
        window_width_ = MIN_WINDOW_WIDTH;
    }
    else 
    {
        window_width_ = window_width;
    }

    // Если задаваемая высота окна меньше минимальной, устанавливаем минимальную
    if (window_width < MIN_WINDOW_HEIGHT)
    {
        window_height_ = MIN_WINDOW_HEIGHT;
    }
    else 
    {
        window_height_ = window_height;
    }

    // Рассчитываем размер занимаемый кирпичами по оси X, по оси Y устанавливается по умолчанию
    count_blocks_x = ((window_width_ - EDGE_INDENT * 2) - ((window_width_ - EDGE_INDENT * 2) / BLOCK_WIDTH) * INDENT_BETWEEN_BRICKS) / BLOCK_WIDTH;
    count_blocks_y = 7;

    window_ = std::unique_ptr<RenderWindow>(new sf::RenderWindow(sf::VideoMode(window_width_, window_height_), "Arkanoid"));
    platform_ = std::make_shared<platform>(window_width_ / 2, window_height_ - 50, 200, 20, 6);
    ball_ = std::make_shared<ball>(window_width_ / 2, window_height_ / 2, 11, 7);

    // Ограничиваем частоту кадров
    window_->setFramerateLimit(240);

    set_bricks();
}


// Устанавливает кирпичи на игровую площадку
void game::set_bricks()
{
    for (size_t i = 0; i < count_blocks_x; i++)
    {
        for (size_t j = 0; j < count_blocks_y; j++)
        {
            if ( (i + j) % 2 == 0)
            {
                bricks_.emplace_back(std::make_shared<brick>((i + 1) * (BLOCK_WIDTH + INDENT_BETWEEN_BRICKS) + EDGE_INDENT, 
                                                             (j + 2) * (BLOCK_HEIGHT + INDENT_BETWEEN_BRICKS),
                                                             BLOCK_WIDTH, BLOCK_HEIGHT));
            }
        }
    }

}

// Начать игру заново
void game::start_over()
{
    sleep(2);

    set_bricks();

    ball_->shape_.setPosition(window_width_ / 2, window_height_ / 2);
    ball_->ball_speed_ = 1;
    ball_->speed_.x = 0;
    ball_->speed_.y = ball_->ball_speed_;
}


// Запускает игру
void game::run()
{
    while(window_->isOpen())
    {
        // Устанавливаем необходимый цвет окну
        window_->clear(Color{70, 75, 100});

        // Обработка выхода при нажатии Esc
        if(Keyboard::isKeyPressed(Keyboard::Key::Escape)) 
            window_->close();

        Event event;

        //Обработка выхода при нажатии крестика на окне
        while (window_->pollEvent(event))
            if (event.type == sf::Event::Closed)
                window_->close();
        
        // Обновить позицию мяча
        ball_->update(window_width_, window_height_);

        // Обновить позицию платформы
        platform_->update(window_width_, window_height_);

        // Проверить ударяется ли мяч о платформу
        check_collision(platform_, ball_);

        // Проверить вышел ли мяч за пределы нижней границы окна
        if (check_collision(ball_, window_width_, window_height_))
        {
            start_over();
        }

        // Для каждого кирпича проверяем, не ударился ли мяч об него
        for(const auto& brick_ : bricks_) 
        {  
            check_collision(brick_, ball_);
        }

        // Удаляем кирпич, если он разрушен
        bricks_.erase(remove_if(begin(bricks_), end(bricks_),
                         [](const std::shared_ptr<brick> brick_)
                         {
                             return brick_->is_destroyed();
                         }),
                     end(bricks_));


        // Если все кирпичи разрушены, начать заново
        if (bricks_.empty()) 
        {
            start_over();
        }

        // Отрисовываем все элементы игры
        window_->draw(ball_->shape_);
        window_->draw(platform_->shape_);

        for(const auto& brick_ : bricks_)
        {
            window_->draw(brick_->shape_);
        }

        window_->display();
    }
}


uint16_t game::get_window_width() const
{
    return window_width_;
}


uint16_t game::get_window_height() const
{
    return window_height_;
}
