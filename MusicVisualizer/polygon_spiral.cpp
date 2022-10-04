#include "polygon_spiral.h"

#include <iostream>
#include <algorithm>

#include "../Utilities/draw_utilities.h"
#include "polygon_layer.h"

PolygonSpiralLayer::PolygonSpiralLayer(int num_sides, int window_width, int window_height,
    double position, double rotation_rate, double scale_rate, int wave_amplitude, SDL_Color wave_color)
    : sides(num_sides), intersect_position(std::max(0.0, std::min(1.0, position))),
        rotation_rate(rotation_rate), scale_rate(std::max(0.75, std::min(1.5, scale_rate))), amplitude(wave_amplitude), color(wave_color) {
    double corner_distance = std::sqrt(std::pow(window_height / 2.0, 2.0) + std::pow(window_height / 2.0, 2.0));
    min_radius = 2.0 * corner_distance + abs(double(amplitude));
    max_radius = 2.0 * min_radius;
    centre = SDL_Point{ window_width / 2, window_height / 2 };
    outer_vertices = pixel_to_float_points(PolygonLayer(sides, int(min_radius * 1.5), centre, 0.0, wave_amplitude, color).get_vertices());
}

void PolygonSpiralLayer::draw(SDL_Renderer * const renderer, const wave & signal) {
    outer_vertices = scale(outer_vertices, scale_rate, pixel_to_float_point(centre));
    outer_vertices = rotate(outer_vertices, pixel_to_float_point(centre), rotation_rate);

    generate_polygons();

    CompositeLayer::draw(renderer, signal);
}

void PolygonSpiralLayer::add_outer_polygon() {
    // This is a load of guff. And probably not the best way to do it.
    // We use the cosine rule repeatedly to figure out the radius (distance from centre to vertices)
    // and angle of rotation (relative to inner polygon) of the outer polygon.
    auto inner_vertices = outer_vertices;
    double p = intersect_position; // For brevity.

    double central_angle = 2.0 * M_PI / double(sides);
    double outer_angle = M_PI * double(sides - 2) / double(sides);
    double inner_radius = distance(inner_vertices.front(), pixel_to_float_point(centre));

    // Use the (isoceles) cosine rule to calculate the inner polygon side length.
    double inner_side_length_squared = 2.0 * inner_radius * inner_radius * (1.0 - cos(central_angle));

    // Use the (bastard) cosine rule to calculate the outer polygon side length.
    double outer_side_length_squared = inner_side_length_squared / ((1.0 - 2.0 * p + 2.0 * p * p) - 2.0 * p * (1.0 - p) * cos(outer_angle));

    // Use the outer side length to calculate the outer radius.
    double outer_radius = sqrt(outer_side_length_squared / 2.0 / (1.0 - cos(central_angle)));
    SDL_assert(outer_radius >= 0.0);

    // Use the radii with the (ubiquitous) cosine rule to calculate the rotation between the inner and outer vertices.
    double outer_side_length = sqrt(outer_side_length_squared);
    double cos_rot = (outer_radius * outer_radius + inner_radius * inner_radius
        - (p * p * outer_side_length_squared)) / (2.0 * outer_radius * inner_radius);
    double rotation = acos(cos_rot);

    // Scale and rotate the inner vertices to get the outer vertices;
    outer_vertices = scale(inner_vertices, outer_radius / inner_radius, pixel_to_float_point(centre));
    outer_vertices = rotate(outer_vertices, pixel_to_float_point(centre), -rotation); // Check, this might have to be negative based on intersect_position > 0.5....?
}

std::vector<SDL_FPoint> PolygonSpiralLayer::generate_inner_vertices(const std::vector<SDL_FPoint>& polygon_vertices) {
    std::vector<SDL_FPoint> new_vertices;
    for (int j = 0; j < sides; ++j) {
        new_vertices.push_back(SDL_FPoint{ float((1.0 - intersect_position) * polygon_vertices[j].x + intersect_position * polygon_vertices[(j + 1) % sides].x),
                                          float((1.0 - intersect_position) * polygon_vertices[j].y + intersect_position * polygon_vertices[(j + 1) % sides].y) });
    }
    return new_vertices;
}

void PolygonSpiralLayer::recentre_outer_vertices() {
    // Translate to compensate for any rounding error shifting the centre.
    float mean_x = 0.0f;
    float mean_y = 0.0f;
    for (const auto& v : outer_vertices) {
        mean_x += v.x / sides;
        mean_y += v.y / sides;
    }
    SDL_FPoint shift{ centre.x - mean_x, centre.y - mean_y };
    outer_vertices = translate(outer_vertices, shift);
}

void PolygonSpiralLayer::generate_polygons() {
    clear_layers();
    int wave_amplitude = amplitude;

    // Add or remove outer layer if required.
    double radius = distance(outer_vertices.front(), pixel_to_float_point(centre));
    while (radius > max_radius) {
        outer_vertices = generate_inner_vertices(outer_vertices);
        recentre_outer_vertices();
        radius = distance(outer_vertices.front(), pixel_to_float_point(centre));
    }
    while(radius < min_radius) {
        add_outer_polygon();
        recentre_outer_vertices();
        radius = distance(outer_vertices.front(), pixel_to_float_point(centre));
    }

    auto prev_vertices = outer_vertices;
    while (distance(prev_vertices[0], prev_vertices[1]) > min_distance) {
        auto new_vertices = generate_inner_vertices(prev_vertices);
        wave_amplitude = int(double(wave_amplitude) * 0.9);

        add_layer(std::make_unique<PolygonLayer>(float_to_pixel_points(prev_vertices), centre, 0.0, wave_amplitude, color));
        prev_vertices = new_vertices;
    }
}

