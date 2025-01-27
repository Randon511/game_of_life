#include <chrono>

#include "raylib.h"
#include "../inc/gol.h"

constexpr int loop_time = 500;
constexpr int square_size = 10;
constexpr int num_squares = 50;
constexpr int window_width = num_squares * square_size;
constexpr int window_height = num_squares * square_size;
constexpr Color alive_color = BLACK;
constexpr Color dead_color = WHITE;
constexpr Color line_color = BLACK;
bool first_loop = true;

bool squares[num_squares * num_squares] = {};

using tp = std::chrono::steady_clock::time_point;
tp prev_process_time;

void render_frame()
{
    BeginDrawing();
    ClearBackground(dead_color);

    draw_grid();
    draw_squares();

    EndDrawing();
}

void draw_grid()
{
    // Vertical lines
    for (int i = 0; i < num_squares - 1; i++)
    {
        DrawLine(
            square_size * (i + 1),
            0,
            square_size * (i + 1),
            square_size * num_squares,
            line_color);
    }

    // Horizontal lines
    for (int i = 0; i < num_squares - 1; i++)
    {
        DrawLine(
            0,
            square_size * (i + 1),
            square_size * num_squares,
            square_size * (i + 1),
            line_color);
    }
}

void draw_squares()
{
    for (int i = 0; i < (num_squares * num_squares); i++)
    {
        if (squares[i])
        {
            int ypos = (i / num_squares) * square_size;
            int xpos = (i % num_squares) * square_size;
            DrawRectangle(xpos, ypos, square_size, square_size, alive_color);
        }
    }
}

void check_lives()
{
}

void process_game()
{
    check_lives();
    render_frame();
}

int main()
{
    InitWindow(window_width, window_height, "GOL");

    while (!WindowShouldClose())
    {
        tp current_time = std::chrono::steady_clock::now();
        std::chrono::milliseconds elapsed_time =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                current_time - prev_process_time);

        if (elapsed_time.count() >= loop_time || first_loop)
        {
            process_game();
            first_loop = false;
            prev_process_time = std::chrono::steady_clock::now();
        }
    }

    CloseWindow();

    return 0;
}
