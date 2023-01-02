#pragma once

#include <vector>

#include "SDL.h"

// Calculate the distance between two points
int distance(const SDL_Point& v_1, const SDL_Point& v_2);

// Calculate the distance between two points
double distance(const SDL_FPoint& v_1, const SDL_FPoint& v_2);

// Calculate the angle from horizontal of the line between two points
double angle(const SDL_Point& v_1, const SDL_Point& v_2);

// Calculate the angle from horizontal of the line between two points
double angle(const SDL_FPoint& v_1, const SDL_FPoint& v_2);

// Convert a point from float to pixel (int)
SDL_Point float_to_pixel_point(const SDL_FPoint& p);

// Convert a point from pixel (int) to float
SDL_FPoint pixel_to_float_point(const SDL_Point& p);

// Convert a vector of points from float to pixel (int)
std::vector<SDL_Point> float_to_pixel_points(const std::vector<SDL_FPoint>& points);

// Convert a vector of points from pixel (int) to float
std::vector<SDL_FPoint> pixel_to_float_points(const std::vector<SDL_Point>& points);

// Translate a single point
SDL_Point translate_point(const SDL_Point & v, const SDL_Point & translation);

// Translate a single point
SDL_FPoint translate_point(const SDL_FPoint & v, const SDL_FPoint & translation);

// Translate a vector of points
std::vector<SDL_Point> translate(const std::vector<SDL_Point>& points, const SDL_Point & translation);

// Translate a vector of points
std::vector<SDL_FPoint> translate(const std::vector<SDL_FPoint>& points, const SDL_FPoint & translation);

// Rotate a single point about the centre
SDL_Point rotate_point(const SDL_Point &v, const SDL_Point &centre, double radians);

// Rotate a single point about the centre
SDL_FPoint rotate_point(const SDL_FPoint &v, const SDL_FPoint &centre, double radians);

// Rotate a vector of points about the centre
std::vector<SDL_Point> rotate(const std::vector<SDL_Point>& points, const SDL_Point & centre, double radians);

// Rotate a vector of points about the centre
std::vector<SDL_FPoint> rotate(const std::vector<SDL_FPoint>& points, const SDL_FPoint & centre, double radians);

// Scale a vector of points about (0,0)
std::vector<SDL_Point> scale(const std::vector<SDL_Point> & points, double scale_factor);

// Scale a vector of points about (0,0)
std::vector<SDL_FPoint> scale(const std::vector<SDL_FPoint> & points, double scale_factor);

// Scale a vector of points about some centre
std::vector<SDL_Point> scale(const std::vector<SDL_Point> & points, double scale_factor, const SDL_Point& centre);

// Scale a vector of points about some centre
std::vector<SDL_FPoint> scale(const std::vector<SDL_FPoint> & points, double scale_factor, const SDL_FPoint& centre);

// Interpolate the points on a straight line
std::vector<SDL_Point> interpolate_line(const SDL_Point & v_1, const SDL_Point & v_2, int num_points);

// Find the point at a fixed poisition on the line between them
SDL_Point point_on_line(const SDL_Point & v_1, const SDL_Point & v_2, double position);

// Generate a wave of pixel points
// param: wave - the amplitude of each point on the wave
// param: length - the pixel length of the wave
// param: amplitude - the maximum pixel amplitude of the wave
std::vector<SDL_Point> gen_wave_points(std::vector<float> wave, int length, int amplitude);

// Draw a circle with the given renderer
void draw_circle(SDL_Renderer * const renderer, const SDL_Point & centre, int radius, const SDL_Color & color, int thickness=0);

// Compute the perimeter points for a single octant
std::vector<SDL_Point> bresenhams_circle_points(int r);


// Draw a wave with the given renderer
void draw_wave(SDL_Renderer * const renderer, const std::vector<float> &wave, const SDL_Point &start, const SDL_Point & end, int amplitude, const SDL_Color& color);

// Draw a filled wave with the given renderer
void draw_wave_fill(SDL_Renderer * const renderer, const std::vector<float> &wave, const SDL_Point &start, const SDL_Point & end, int amplitude, const SDL_Color& color);

// Draw bars with the given renderer
void draw_vertical_bars(SDL_Renderer * const renderer, std::vector<float> bar_values, const SDL_Point &start, const SDL_Point & end, int amplitude, int gap_width, const SDL_Color& color);
