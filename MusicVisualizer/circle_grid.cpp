#include "circle_grid.h"

#include <algorithm>

#include "amplitude_circle_layer.h"

CircleGridLayer::CircleGridLayer(const std::vector<SDL_Color> & colors, int rows, int cols, int screen_width, int screen_height) {
    int row_spacing = screen_height / (rows * 2);
    int col_spacing = screen_width / (cols * 2);
    int outer_radius = std::min(row_spacing, col_spacing);
    for (int i = 0; i < colors.size(); ++i) {
        int radius = outer_radius * (int(colors.size()) - i) / int(colors.size()) / 2;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                SDL_Point centre{ col_spacing * (1 + 2 * c), row_spacing * (1 + 2 * r) };
                add_layer(std::make_unique<AmplitudeCircleLayer>(centre, radius, colors[i]));
            }
        }
    }
}

