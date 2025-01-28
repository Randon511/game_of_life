#include <chrono>

#include "raylib.h"
#include "../inc/gol.h"

constexpr int loop_time = 100;
constexpr int square_size = 10;
constexpr int num_cols = 100;
constexpr int num_rows = 100;
constexpr int num_cells = num_cols * num_rows;
constexpr int window_width = num_cols * square_size;
constexpr int window_height = num_rows * square_size;
constexpr Color alive_color = BLACK;
constexpr Color dead_color = WHITE;
constexpr Color line_color = BLACK;
bool first_loop = true;

struct cell
{
    bool current_state;
    bool next_state;
};

cell cells[num_cells] = {};

using tp = std::chrono::steady_clock::time_point;
tp prev_process_time;

void render_frame()
{
    BeginDrawing();
    ClearBackground(dead_color);

    draw_grid();
    draw_cells();

    EndDrawing();
}

void draw_grid()
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

void draw_cells()
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

void check_lives()
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

void update_lives()
{
    for (int i = 0; i < num_cells; i++)
    {
        cells[i].current_state = cells[i].next_state;
    }
}

void process_game()
{
    check_lives();
    render_frame();
    update_lives();
}

void init_cells()
{
    for (int i = 0; i < num_cells; i++)
    {
        if ((i % 5) == 0)
        {
            cells[i].next_state = true;
        }
    }
}

int main()
{
    InitWindow(window_width, window_height, "GOL");

    init_cells();

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
