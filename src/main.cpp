#include "game.h"

int main()
{
    std::unique_ptr<game> game_obj(new game());

    game_obj->run();
}