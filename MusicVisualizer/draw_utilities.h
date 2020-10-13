#pragma once

#include <vector>

#include "SDL.h"

// Calculate the distance between two points
int distance(const SDL_Point& v_1, const SDL_Point& v_2);

// Calculate the angle from horizontal of the line between two points
double angle(const SDL_Point& v_1, const SDL_Point& v_2);

// Translate a vector of points
std::vector<SDL_Point> translate(const std::vector<SDL_Point>& points, const SDL_Point & translation);

// Rotate a single point about the centre
SDL_Point rotate_point(const SDL_Point &v, const SDL_Point &centre, double radians);

// Rotate a vector of points about the centre
std::vector<SDL_Point> rotate(const std::vector<SDL_Point>& points, const SDL_Point & centre, double radians);

// Generate a wave of pixel points
// param: wave - the amplitude of each point on the wave
// param: length - the pixel length of the wave
// param: amplitude - the maximum pixel amplitude of the wave
std::vector<SDL_Point> gen_wave_points(std::vector<float> wave, int length, int amplitude);

// Draw a circle with the given renderer
void draw_circle(SDL_Renderer * const renderer, const SDL_Point &centre, int radius, const SDL_Color& color);

// Draw a wave with the given renderer
void draw_wave(SDL_Renderer * const renderer, const std::vector<float> &wave, const SDL_Point &start, const SDL_Point & end, int amplitude, const SDL_Color& color);
