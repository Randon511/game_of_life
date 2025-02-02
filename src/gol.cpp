#include "../inc/gol.h"
#include "imgui.h"
#include "raylib.h"
#include "rlImGui.h"

using namespace game;

GOL::GOL()
    : state(GameState::INIT),
      first_loop(true),
      cells{},
      prev_process_time(std::chrono::steady_clock::now())
{
}

void GOL::setup_game()
{
    InitWindow(window_width, window_height, "GOL");
    rlImGuiSetup(true);

    // init_cells();
    game_running = true;
}

void GOL::destroy_game()
{
    CloseWindow();
}

void GOL::process_game()
{
    if (WindowShouldClose())
    {
        game_running = false;
    }
    // process gui inputs
    // process state machine
    process_sm();
}

void GOL::process_sm()
{
    switch (state)
    {
    case GameState::INIT:
        init_state_handler();
        break;
    case GameState::RUNNING:
        running_state_handler();
        break;
    case GameState::PAUSED:
        paused_state_handler();
        break;
    default:
        break;
    }
}

void GOL::init_state_handler()
{
    render_frame();
}

void GOL::running_state_handler()
{
    tp current_time = std::chrono::steady_clock::now();
    std::chrono::milliseconds elapsed_time =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            current_time - prev_process_time);

    if (elapsed_time.count() >= loop_time || first_loop)
    {
        check_lives();
        render_frame();
        update_lives();

        first_loop = false;
        prev_process_time = std::chrono::steady_clock::now();
    }
}

void GOL::paused_state_handler()
{
}

void GOL::render_frame()
{
    BeginDrawing();
    ClearBackground(dead_color);

    rlImGuiBegin();
    ImGui::ShowDemoWindow();

    draw_grid();
    draw_cells();

    rlImGuiEnd();
    EndDrawing();
}

void GOL::draw_grid()
{
    // Vertical lines
    for (int i = 0; i < num_rows - 1; i++)
    {
        DrawLine(
            square_size * (i + 1),
            0,
            square_size * (i + 1),
            square_size * num_rows,
            line_color);
    }

    // Horizontal lines
    for (int i = 0; i < num_cols - 1; i++)
    {
        DrawLine(
            0,
            square_size * (i + 1),
            square_size * num_cols,
            square_size * (i + 1),
            line_color);
    }
}

void GOL::draw_cells()
{
    for (int i = 0; i < num_cells; i++)
    {
        if (cells[i].next_state)
        {
            int ypos = (i / num_rows) * square_size;
            int xpos = (i % num_cols) * square_size;
            DrawRectangle(xpos, ypos, square_size, square_size, alive_color);
        }
    }
}

void GOL::check_lives()
{
    for (int i = 0; i < num_cells; i++)
    {
        int num_alive_neighbors = 0;
        // Above
        if ((i / num_cols) > 0)
        {
            num_alive_neighbors += cells[i - num_cols].current_state;

            // Top right
            if ((i % num_cols) != (num_cols - 1))
            {
                num_alive_neighbors += cells[i - num_cols + 1].current_state;

                // Right
                num_alive_neighbors += cells[i + 1].current_state;
            }

            // Top left
            if ((i % num_cols) != 0)
            {
                num_alive_neighbors += cells[i - num_cols - 1].current_state;

                // Left
                num_alive_neighbors += cells[i - 1].current_state;
            }
        }

        // Below
        if ((i / num_cols) != (num_rows - 1))
        {
            num_alive_neighbors += cells[i + num_cols].current_state;

            // Bottom right
            if ((i % num_cols) != (num_cols - 1))
            {
                num_alive_neighbors += cells[i + num_cols + 1].current_state;
            }

            // Bottom right
            if ((i % num_cols) != 0)
            {
                num_alive_neighbors += cells[i + num_cols - 1].current_state;
            }
        }

        // Logic for alive cells
        if (cells[i].current_state)
        {
            if ((num_alive_neighbors < 2) || (num_alive_neighbors > 3))
            {
                cells[i].next_state = false;
            }
        }
        else
        {
            if (num_alive_neighbors == 3)
            {
                cells[i].next_state = true;
            }
        }
    }
}

void GOL::update_lives()
{
    for (int i = 0; i < num_cells; i++)
    {
        cells[i].current_state = cells[i].next_state;
    }
}

void GOL::init_cells()
{
    for (int i = 0; i < num_cells; i++)
    {
        if ((i % 3) == 0)
        {
            cells[i].next_state = true;
        }
    }
}
