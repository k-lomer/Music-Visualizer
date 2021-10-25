#include "polygon_spiral.h"

#include <algorithm>

#include "../Utilities/draw_utilities.h"
#include "polygon_layer.h"

PolygonSpiralLayer::PolygonSpiralLayer(int num_sides, int window_width, int window_height,
    int iterations, double position, double rotation_rate, int wave_amplitude, SDL_Color wave_color)
    : window_height(window_height), window_width(window_width), iters(iterations), intersect_position(std::max(0.0, std::min(1.0, position))),
    rotation_rate(rotation_rate), amplitude(wave_amplitude), color(wave_color){
    SDL_Point poly_centre = SDL_Point{ window_width / 2, window_height / 2};
    int radius = std::min(window_height, window_width) / 2;

    std::unique_ptr<PolygonLayer> prev_layer = std::make_unique<PolygonLayer>(num_sides, radius, poly_centre, rotation_rate, wave_amplitude, wave_color);
    for (int i = 0; i < iterations; ++i) {
        std::vector<SDL_Point> prev_vertices = prev_layer->get_vertices();
        std::vector<SDL_Point> new_vertices;
        for (int j = 0; j < num_sides; ++j) {
            new_vertices.push_back(SDL_Point{ int((1 - intersect_position) * prev_vertices[j].x + intersect_position * prev_vertices[(j + 1) % num_sides].x),
                                              int((1 - intersect_position) * prev_vertices[j].y + intersect_position * prev_vertices[(j + 1) % num_sides].y) });
        }
        wave_amplitude = int(double(wave_amplitude) * 0.95);
        std::unique_ptr<PolygonLayer> new_layer = std::make_unique<PolygonLayer>(new_vertices, poly_centre, rotation_rate, wave_amplitude, wave_color);
        add_layer(std::move(prev_layer));
        prev_layer = std::move(new_layer);
    }
    add_layer(std::move(prev_layer));
}
