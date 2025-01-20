#include <cstdio>
#include <chrono>
#include <thread>
#include "raylib.h"

static constexpr int window_width = 100;
static constexpr int window_height = 100;
static constexpr int loop_time = 10;

int main()
{
    InitWindow(window_width, window_height, "GOL");

    while (!WindowShouldClose())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(loop_time));
    }

    CloseWindow();

    return 0;
}