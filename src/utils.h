#pragma once

#include "platform.h"
#include "ball.h"
#include "brick.h"

// Проверяем пересекаются ли объекты
template <class T1, class T2>
bool isIntersecting(std::shared_ptr<T1> a, std::shared_ptr<T2> b)
{
    return a->right() >= b->left() && a->left() <= b->right() &&
           a->bottom() >= b->top() && a->top() <= b->bottom();
}

// Проверяем пересекается ли платформа с мячем и если да, то меняем направление мяча
void check_collision(std::shared_ptr<platform> platform_, std::shared_ptr<ball> ball_)
{
    if (!isIntersecting(platform_, ball_)) 
        return;

    ball_->speed_.y = -ball_->ball_speed_;

    if (ball_->get_x() < platform_->get_x())
        ball_->speed_.x = -ball_->ball_speed_;
    else
        ball_->speed_.x = ball_->ball_speed_;
}

// Проверяем пересекается ли кирпич с мячем и если да, меняем прочность мяча или разрушаем его, ускоряем мяч и меняем его направление
void check_collision(std::shared_ptr<brick> brick_, std::shared_ptr<ball> ball_)
{
    if (!isIntersecting(brick_, ball_))
        return;

    // Уменьшаем прочность
    brick_->reduce_strength();

    // Разрушаем блок, если у него нету прочности
    if (brick_->get_strength() == 0)
    {
        brick_->set_destroy(true);
    }
    else 
    {
        brick_->shape_.setFillColor(Color::Yellow);
        ball_->ball_speed_ *= 1.1;
    }

    // Меняем направление мяча

    float overlap_left = ball_->right() - brick_->left();
    float overlap_right = brick_->right() - ball_->left();
    float overlap_top = ball_->bottom() - brick_->top();
    float overlap_bottom = brick_->bottom() - ball_->top();

    bool ball_from_left = abs(overlap_left) < abs(overlap_right);
    bool ball_from_top = abs(overlap_top) < abs(overlap_bottom);

    float min_overlap_x = ball_from_left ? overlap_left : overlap_right;
    float min_overlap_y = ball_from_top ? overlap_top : overlap_bottom;

    if(abs(min_overlap_x) < abs(min_overlap_y))
        ball_->speed_.x = ball_from_left ? -ball_->ball_speed_ : ball_->ball_speed_;
    else
        ball_->speed_.y = ball_from_top ? -ball_->ball_speed_ : ball_->ball_speed_;
}

// Проверяем пересекается ли мяч с нижней частью окна, если да, начинаем новую игру
bool check_collision(std::shared_ptr<ball> ball_, uint16_t window_width, uint16_t window_height) 
{
    //if the ball crosses the red line, return it to the center
    if (int(ball_->get_y() + ball_->radius_) >= window_height) 
    {
        return true;
    }

    return false;
}