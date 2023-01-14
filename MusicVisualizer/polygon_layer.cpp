#include "polygon_layer.h"

#include "../Utilities/draw_utilities.h"

// The vertices are created in this constructor.
// Note that all polygons are initialized with horizontal bottom side.
PolygonLayer::PolygonLayer(int num_sides, int radius, SDL_Point poly_centre, double rotation_rate, int wave_amplitude, SDL_Color wave_color)
    : m_centre(poly_centre), m_rotation_rate(rotation_rate), m_amplitude(wave_amplitude), m_color(wave_color) {
    SDL_Point first_point = rotate_point(SDL_Point{poly_centre.x, poly_centre.y + radius}, poly_centre, 2*M_PI/num_sides / 2);
    m_vertices.push_back(first_point);
    for (int i = 1; i < num_sides; ++i) {
        m_vertices.push_back(rotate_point(first_point, poly_centre, 2 * M_PI * i / num_sides));
    }
}

PolygonLayer::PolygonLayer(const std::vector<SDL_Point> & poly_vertices, SDL_Point poly_centre, double rotation_rate, int wave_amplitude, SDL_Color wave_color)
    : m_vertices(poly_vertices), m_centre(poly_centre), m_rotation_rate(rotation_rate), m_amplitude(wave_amplitude), m_color(wave_color) {}


void PolygonLayer::draw(SDL_Renderer * renderer, const wave & signal) {
    m_rotation += m_rotation_rate;
    if (m_rotation > 2 * M_PI) {
        m_rotation -= 2 * M_PI;
    }
    else if (m_rotation < 0.0) {
        m_rotation += 2 * M_PI;
    }

    std::vector<SDL_Point> rotated_vertices = rotate(m_vertices, m_centre, m_rotation);

    for (int i = 0; i < rotated_vertices.size(); ++i) {
        draw_wave(renderer, signal, rotated_vertices[i], rotated_vertices[(i+1) % rotated_vertices.size()], -m_amplitude, m_color);
    }
}

std::vector<SDL_Point> PolygonLayer::get_vertices() const {
    return rotate(m_vertices, m_centre, m_rotation);
}
