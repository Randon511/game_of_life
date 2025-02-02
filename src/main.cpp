#include "../inc/gol.h"

int main()
{
    game::GOL gol;

    gol.setup_game();

    while (gol.game_running)
    {
        gol.process_game();
    }

    gol.destroy_game();

    return 0;
}
