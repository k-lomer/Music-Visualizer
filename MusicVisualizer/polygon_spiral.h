#pragma once

#include "composite_layer.h"

// A spiralling sequence of regular polygons shrinking towards the centre or growing out.
class PolygonSpiralLayer : public virtual CompositeLayer {
public:
    // PolygonSpiralLayer constructor.
    // param: num_sides                             - the number of sides of the regular polygon
    // param: window_width                          - the pixel width of the window
    // param: window_height                         - the pixel height of the window
    // param: position                              - how far along the edge to begin the next iteration (between 0 and 1)
    // param: rotation_rate                         - the degrees to rotate per frame
    // param: scale_rate                            - the rate at which the polygons scale up (>1) or scale down (<1)
    // param: wave_amplitude                        - the maximum pixel amplitude of the waves on the sides
    // param: wave_color                            - the color of the waves on the sides
    PolygonSpiralLayer(int num_sides, int window_width, int window_height, double position, double rotation_rate, double scale_rate, int wave_amplitude, SDL_Color wave_color);

    // Draw the PolygonSpiralLayer.
    // param: renderer                              - the renderer to draw the PolygonSpiralLayer
    // param: signal                                - the signal to draw
    void draw(SDL_Renderer * const renderer, const wave & signal) override;

private:
    // The minimum radius for the outermost polygon.
    double m_min_radius;
    // The maximum radius for the outermost polygon.
    double m_max_radius;
    // The maximum amplitude for the waves on the sides of the polygons.
    int m_amplitude;
    // The intersection position on the edges of a polygon which mark the vertices of the next iteration of polygon inside, controls the steepness of the spiral.
    double m_intersect_position;
    // The color to draw the polygons.
    SDL_Color m_color;
    // The centre of the polygons.
    SDL_Point m_centre;
    // The rate at which to rotate the polygons.
    double m_rotation_rate;
    // The rate at which to scale the polygons.
    double m_scale_rate;
    // The number of sides for the polygons.
    int m_sides;
    // The (ordered) vertices which make up the outer polygon.
    std::vector<SDL_FPoint> m_outer_vertices;
    // The minimum distance between vertices below which no new polygons will be drawn.
    const int m_min_distance = 20;

    // Add an outer polygon to the spiral.
    void add_outer_polygon();

    // Generate the vertices of the next polygon, within the current one.
    // param: polygon_vertices                      - the vertices of the current polygon.
    // return: std::vector<SDL_FPoint>              - the vertices of the next polygon.
    std::vector<SDL_FPoint> generate_inner_vertices(const std::vector<SDL_FPoint>& polygon_vertices);

    // Generate the polygons for the spiral based on the current values.
    void generate_polygons();

    // Recentre the outer vertices.
    // Needed as the rotation and scaling can cause them to drift.
    void recentre_outer_vertices();
};
