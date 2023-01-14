#pragma once

#include <vector>

#include "SDL.h"
#include "visual_layer.h"

// A class which is a polygon whose sides are audio waves.
class PolygonLayer : public VisualLayer {
public:
    // PolygonLayer constructor for a regular polygon using a number of sides and a radius.
    // param: num_sides - the number of sides of the regular polygon
    // param: radius - the pixel distance from the centre to a vertex
    // param: poly_centre - the coordinates of the centre of the polygon
    // param: rotation_rate - the radians to rotate per frame
    // param: wave_amplitude - the maximum pixel amplitude of the waves on the sides
    // param: wave_color - the color of the waves on the sides
    PolygonLayer(int num_sides, int radius, SDL_Point poly_centre, double rotation_rate, int wave_amplitude, SDL_Color wave_color);

    // PolygonLayer constructor using pre-defined ordered vertices.
    // param: vertices - the vertices which make up the polygon
    // param: poly_centre - the coordinates of the centre of the polygon
    // param: rotation_rate - the radians to rotate per frame
    // param: wave_amplitude - the maximum pixel amplitude of the waves on the sides
    // param: wave_color - the color of the waves on the sides
    PolygonLayer(const std::vector<SDL_Point> & poly_vertices, SDL_Point poly_centre, double rotation_rate, int wave_amplitude, SDL_Color wave_color);

    // Draw the PolygonLayer.
    // param: renderer                      - the renderer to draw the PolygonLayer.
    // param: signal                        - the signal to draw.
    virtual void draw(SDL_Renderer * renderer, const wave & signal) override;

    // Get the vertices defining this polygon.
    // return: std::vector<SDL_Point>       - the vertices
    std::vector<SDL_Point> get_vertices() const;

    // Set the rotation about the centre for this polygon.
    // param: rot                           - the rotation in radians
    void set_rotation(double rot) {m_rotation = rot;}

    // Get the rotation about the centre for this polygon.
    // param: double                        - the rotation in radians
    double get_rotation() const {return m_rotation;}

private:
    // The centre coordinates of this polygon.
    SDL_Point m_centre;
    // The maximum aplitude of the waves on the edges.
    int m_amplitude;
    // The color to draw this polygon.
    SDL_Color m_color;
    // The ordered vertices which make up the polygon.
    std::vector<SDL_Point> m_vertices;
    // The rate of rotation.
    double m_rotation_rate;
    // The current rotation.
    double m_rotation = 0.0;
};
