#pragma once

#include "visual_layer.h"

// A class which is a regular polygon whose sides are audio waves
class PolygonLayer : public VisualLayer {
public:
    // param: num_sides - the number of sides of the regular polygon
    // param: radius - the pixel distance from the centre to a vertex
    // param: poly_centre - the coordinates of the centre of the polygon
    // param: rotation_rate - the degrees to rotate per frame
    // param: wave_amplitude - the maximum pixel amplitude of the waves on the sides
    // param: wave_color - the color of the waves on the sides
    PolygonLayer(int num_sides, int radius, SDL_Point poly_centre, double rotation_rate, int wave_amplitude, SDL_Color wave_color);

    virtual void draw(SDL_Renderer * renderer, const packet & packet_buffer) override;

private:
    SDL_Point centre;
    int amplitude;
    SDL_Color color;
    // the vertices which make up the polygon (ordered)
    std::vector<SDL_Point> vertices;
    double rotation_rate;
};
