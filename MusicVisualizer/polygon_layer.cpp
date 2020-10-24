#include "polygon_layer.h"

#include "draw_utilities.h"

// The vertices are created in this constructor
// Note that all polygons are initialized with horizontal bottom side
PolygonLayer::PolygonLayer(int num_sides, int radius, SDL_Point poly_centre, double rotation_rate, int wave_amplitude, SDL_Color wave_color)
    : centre(poly_centre), rotation_rate(rotation_rate), amplitude(wave_amplitude), color(wave_color) {
    SDL_Point first_point = rotate_point(SDL_Point{poly_centre.x, poly_centre.y + radius}, poly_centre, 2*M_PI/num_sides / 2);
    vertices.push_back(first_point);
    for (int i = 1; i < num_sides; ++i) {
        vertices.push_back(rotate_point(first_point, poly_centre, 2 * M_PI * i / num_sides));
    }
}

void PolygonLayer::draw(SDL_Renderer * renderer, const SignalBox & signal_box) {
    rotation += rotation_rate;
    if (rotation > 2 * M_PI) {
        rotation -= 2 * M_PI;
    }
    else if (rotation < 0.0) {
        rotation += 2 * M_PI;
    }

    std::vector<SDL_Point> rotated_vertices = rotate(vertices, centre, rotation);
    auto wave = signal_box.gen_wave(signal_type);

    for (int i = 0; i < rotated_vertices.size(); ++i) {
        draw_wave(renderer, wave, rotated_vertices[i], rotated_vertices[(i+1) % rotated_vertices.size()], -amplitude, color);
    }
}
