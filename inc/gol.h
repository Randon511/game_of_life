#ifndef _GOL_H_
#define _GOL_H_

#include <cstdint>
#include <chrono>

#include "consts.h"
#include "rlImGui.h"

namespace game
{
class GOL

{
  public:
    GOL();

    void setup_game();
    void process_game();
    void destroy_game();

    bool game_running;

  private:
    using tp = std::chrono::steady_clock::time_point;

    struct cell
    {
        bool current_state;
        bool next_state;
    };

    enum class GameState : uint8_t
    {
        INIT = 0,
        RUNNING = 1,
        PAUSED = 2
    };

    void render_frame();
    void check_lives();
    void draw_grid();
    void draw_cells();
    void update_lives();
    void init_cells();
    void process_sm();

    void init_state_handler();
    void running_state_handler();
    void paused_state_handler();

    GameState state;
    bool first_loop;
    cell cells[num_cells];
    tp prev_process_time;
}; // class GOL
} // namespace game

#endif
