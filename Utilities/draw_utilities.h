#pragma once

#include <vector>

#include "SDL.h"

// Calculate the integer distance between two pixel (int) points.
// param: p_1                           - a pixel (int) point
// param: p_2                           - a pixel (int) point
// return: int                          - the integer distance between the points
int distance(const SDL_Point& p_1, const SDL_Point& p_2);

// Calculate the distance between two float points.
// param: p_1                           - a float point
// param: p_2                           - a float point
// return: double                       - the distance between the points
double distance(const SDL_FPoint& p_1, const SDL_FPoint& p_2);

// Calculate the angle from horizontal of the line between two integer pixel points.
// param: p_1                           - a pixel (int) point
// param: p_2                           - a pixel (int) point
// return: double                       - the angle between the points
double angle(const SDL_Point& p_1, const SDL_Point& p_2);

// Calculate the angle from horizontal of the line between two points.
// param: p_1                           - a float point
// param: p_2                           - a float point
// return: double                       - the angle between the points
double angle(const SDL_FPoint& p_1, const SDL_FPoint& p_2);

// Convert a point from float to pixel (int).
// param: p                             - a float point
// return: SDL_Point                    - the pixel (int) point
SDL_Point float_to_pixel_point(const SDL_FPoint& p);

// Convert a point from pixel (int) to float.
// param: p                             - a pixel (int) point
// return: SDL_FPoint                   - the float point
SDL_FPoint pixel_to_float_point(const SDL_Point& p);

// Convert a vector of points from float to pixel (int).
// param: points                        - the float points
// return: std::vector<SDL_Point>       - the pixel (int) points
std::vector<SDL_Point> float_to_pixel_points(const std::vector<SDL_FPoint>& points);

// Convert a vector of points from pixel (int) to float.
// param: points                        - the pixel (int) points
// return: std::vector<SDL_FPoint>      - the float points
std::vector<SDL_FPoint> pixel_to_float_points(const std::vector<SDL_Point>& points);

// Translate a single pixel (int) point.
// param: p                             - the pixel (int) point
// param: translation                   - the amount to translate the point
// return: SDL_Point                    - the translated point
SDL_Point translate_point(const SDL_Point & p, const SDL_Point & translation);

// Translate a single float point.
// param: p                             - the float point
// param: translation                   - the amount to translate the point
// return: SDL_FPoint                   - the translated point
SDL_FPoint translate_point(const SDL_FPoint & p, const SDL_FPoint & translation);

// Translate a vector of pixel (int) points.
// param: points                        - the pixel (int) points
// return: std::vector<SDL_Point>       - the translated points
std::vector<SDL_Point> translate(const std::vector<SDL_Point>& points, const SDL_Point & translation);

// Translate a vector of float points.
// param: points                        - the float points
// return: std::vector<SDL_FPoint>      - the translated points
std::vector<SDL_FPoint> translate(const std::vector<SDL_FPoint>& points, const SDL_FPoint & translation);

// Rotate a single pixel (int) point about the centre.
// param: p                             - the pixel (int) point
// param: centre                        - the pixel (int) centre to rotate about
// param: radians                       - the amount to rotate the point about the centre
// return: SDL_Point                    - the rotated pixel (int) point
SDL_Point rotate_point(const SDL_Point &p, const SDL_Point &centre, double radians);

// Rotate a single float point about the centre.
// param: p                             - the float point
// param: centre                        - the float centre to rotate about
// param: radians                       - the amount to rotate the point about the centre
// return: SDL_FPoint                   - the rotated float point
SDL_FPoint rotate_point(const SDL_FPoint &p, const SDL_FPoint &centre, double radians);

// Rotate a vector of pixel (int) points about the centre.
// param: points                        - the pixel (int) points
// param: centre                        - the pixel (int) centre to rotate about
// param: radians                       - the amount to rotate the points about the centre
// return: std::vector<SDL_Point>       - the rotated pixel (int) points
std::vector<SDL_Point> rotate(const std::vector<SDL_Point>& points, const SDL_Point & centre, double radians);

// Rotate a vector of float points about the centre.
// param: points                        - the float points
// param: centre                        - the float centre to rotate about
// param: radians                       - the amount to rotate the points about the centre
// return: std::vector<SDL_FPoint>      - the rotated float points
std::vector<SDL_FPoint> rotate(const std::vector<SDL_FPoint>& points, const SDL_FPoint & centre, double radians);

// Scale a vector of pixel (int) points about (0,0).
// param: points                        - the pixel (int) point
// param: scale_factor                  - the amount to scale the points
// return: std::vector<SDL_Point>       - the scaled pixel (int) points
std::vector<SDL_Point> scale(const std::vector<SDL_Point> & points, double scale_factor);

// Scale a vector of float points about (0,0).
// param: points                        - the float point
// param: scale_factor                  - the amount to scale the points
// return: std::vector<SDL_FPoint>      - the scaled float points
std::vector<SDL_FPoint> scale(const std::vector<SDL_FPoint> & points, double scale_factor);

// Scale a vector of pixel (int) points about some centre.
// param: points                        - the pixel (int) point
// param: scale_factor                  - the amount to scale the points
// param: centre                        - the centre to scale the points about
// return: std::vector<SDL_Point>       - the scaled pixel (int) points
std::vector<SDL_Point> scale(const std::vector<SDL_Point> & points, double scale_factor, const SDL_Point& centre);

// Scale a vector of float points about some centre.
// param: points                        - the float point
// param: scale_factor                  - the amount to scale the points
// param: centre                        - the centre to scale the points about
// return: std::vector<SDL_Point>       - the scaled float points
std::vector<SDL_FPoint> scale(const std::vector<SDL_FPoint> & points, double scale_factor, const SDL_FPoint& centre);

// Interpolate the pixel (int) points on a straight line.
// param: p_1                           - the start point of the line
// param: p_2                           - the end point of the line
// param: num_points                    - the number of points to interpolate along the line
// return: std::vector<SDL_Point>       - the pixel (int) points along the line
std::vector<SDL_Point> interpolate_line(const SDL_Point & p_1, const SDL_Point & p_2, int num_points);

// Find the pixel (int) point at a fixed position on a straight line.
// param: p_1                           - the start point of the line
// param: p_2                           - the end point of the line
// param: position                      - the position on the line of the point to find, in the interval [0,1] where 0 is p_1 and 1 is p_2
// return: SDL_Point                    - the point at the given position on the line
SDL_Point point_on_line(const SDL_Point & p_1, const SDL_Point & p_2, double position);

// Generate a wave of pixel points stating at (0,0).
// param: wave                          - the amplitude of each point on the wave
// param: length                        - the pixel length of the wave
// param: amplitude                     - the maximum pixel amplitude of the wave
// return: std::vector<SDL_Point>       - the pixel points on the wave
std::vector<SDL_Point> gen_wave_points(std::vector<float> wave, int length, int amplitude);

// Draw a circle.
// param: renderer                      - the renderer to draw the circle on
// param: centre                        - the pixel (int) point of the centre of the circle
// param: radius                        - the pixel radius of the circle
// param: color                         - the color to draw the circle
// param: thickness                     - the pixel thickness of the circle edge, set as 0 to fill the circle
void draw_circle(SDL_Renderer * const renderer, const SDL_Point & centre, int radius, const SDL_Color & color, int thickness=0);


// Compute the perimeter points for a single octant of breshams circle algorithm.
// param: r                             - the radius of the circle
// return: std::vector<SDL_Point>       - the points on the circle octant
std::vector<SDL_Point> bresenhams_circle_points(int r);

// Draw a wave.
// param: renderer                      - the renderer to draw the wave on
// param: wave                          - the amplitude of the points along the wave
// param: start                         - the pixel (int) start point of the wave
// param: end                           - the pixel (int) end point of the wave
// param: amplitude                     - the maximum pixel amplitude of the wave
// param: color                         - the color to draw the wave
void draw_wave(SDL_Renderer * const renderer, const std::vector<float> &wave, const SDL_Point &start, const SDL_Point & end, int amplitude, const SDL_Color& color);

// Draw a filled wave.
// param: renderer                      - the renderer to draw the wave on
// param: wave                          - the amplitude of the points along the wave
// param: start                         - the pixel (int) start point of the wave
// param: end                           - the pixel (int) end point of the wave
// param: amplitude                     - the maximum pixel amplitude of the wave
// param: color                         - the color to draw the filled wave
void draw_wave_fill(SDL_Renderer * const renderer, const std::vector<float> &wave, const SDL_Point &start, const SDL_Point & end, int amplitude, const SDL_Color& color);

// Draw bars with the given renderer
// param: renderer                      - the renderer to draw the wave on
// param: bar_values                    - the heights of the bars
// param: start                         - the pixel (int) start point of the bars
// param: end                           - the pixel (int) end point of the bars
// param: amplitude                     - the maximum pixel amplitude of the bars
// param: gap_width                     - the maximum pixel gap between bars
// param: color                         - the color to draw the bars
void draw_vertical_bars(SDL_Renderer * const renderer, std::vector<float> bar_values, const SDL_Point &start, const SDL_Point & end, int amplitude, int gap_width, const SDL_Color& color);
