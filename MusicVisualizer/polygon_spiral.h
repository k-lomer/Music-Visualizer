#pragma once

#include "composite_layer.h"

// A spiralling sequence of regular polygons shrinking towards the centre
class PolygonSpiralLayer : public virtual CompositeLayer {
public:
    // param: num_sides - the number of sides of the regular polygon
    // param: window_width - the pixel width of the window
    // param: window_height - the pixel height of the window
    // param: iterations - how many iterations of the spiral to compute
    // param: position - how far along the edge to begin the next iteration (between 0 and 1)
    // param: rotation_rate - the degrees to rotate per frame
    // param: wave_amplitude - the maximum pixel amplitude of the waves on the sides
    // param: wave_color - the color of the waves on the sides
    PolygonSpiralLayer(int num_sides, int window_width, int window_height, int iterations, double position, double rotation_rate, int wave_amplitude, SDL_Color wave_color);

private:
    int window_height;
    int window_width;
    int amplitude;
    double intersect_position;
    int iters;
    SDL_Color color;
    // the vertices which make up the outer polygon (ordered)
    std::vector<SDL_Point> outer_vertices;
    double rotation_rate;
    double rotation = 0.0;
};
