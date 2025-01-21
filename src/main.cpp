#include <cstdio>
#include <chrono>
#include <thread>
#include "raylib.h"

static constexpr int loop_time = 10;
static constexpr int square_size = 10;
static constexpr int num_squares = 50;
static constexpr int window_width = num_squares * square_size;
static constexpr int window_height = num_squares * square_size;
static constexpr Color alive_color = BLACK;
static constexpr Color dead_color = WHITE;
static constexpr Color line_color = BLACK;

void render_frame()
{
    BeginDrawing();
    ClearBackground(dead_color);

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

    EndDrawing();
}

void process_game()
{
}

int main()
{
    InitWindow(window_width, window_height, "GOL");

    while (!WindowShouldClose())
    {
        render_frame();
    }

    CloseWindow();

    return 0;
}