#include <raylib.h>

namespace game
{
constexpr int loop_time = 100;
constexpr int square_size = 10;
constexpr int num_cols = 75;
constexpr int num_rows = 75;
constexpr int num_cells = num_cols * num_rows;
constexpr int window_width = num_cols * square_size;
constexpr int window_height = num_rows * square_size;
constexpr Color alive_color = BLACK;
constexpr Color dead_color = WHITE;
constexpr Color line_color = BLACK;
} // namespace game
