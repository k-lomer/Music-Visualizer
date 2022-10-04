#pragma once

#include "composite_layer.h"

// A spiralling sequence of regular polygons shrinking towards the centre
class PolygonSpiralLayer : public virtual CompositeLayer {
public:
    // param: num_sides - the number of sides of the regular polygon
    // param: window_width - the pixel width of the window
    // param: window_height - the pixel height of the window
    // param: position - how far along the edge to begin the next iteration (between 0 and 1)
    // param: rotation_rate - the degrees to rotate per frame
    // param: scale_rate - the rate at which the polygons scale up (>1) or scale down (<1)
    // param: wave_amplitude - the maximum pixel amplitude of the waves on the sides
    // param: wave_color - the color of the waves on the sides
    PolygonSpiralLayer(int num_sides, int window_width, int window_height, double position, double rotation_rate, double scale_rate, int wave_amplitude, SDL_Color wave_color);

    void draw(SDL_Renderer * const renderer, const wave & signal) override;

private:
    double min_radius;
    double max_radius;
    int amplitude;
    double intersect_position;
    SDL_Color color;
    SDL_Point centre;
    double rotation_rate;
    double scale_rate;
    int sides;
    std::vector<SDL_FPoint> outer_vertices; // the vertices which make up the outer polygon (ordered)
    int min_distance = 20;

    void add_outer_polygon();
    std::vector<SDL_FPoint> generate_inner_vertices(const std::vector<SDL_FPoint>& polygon_vertices);
    void generate_polygons();
    void recentre_outer_vertices();
};
