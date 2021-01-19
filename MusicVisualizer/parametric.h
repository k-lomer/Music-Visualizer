#pragma once

#include <vector>

#include "SDL.h"

// Compute values based on a trigonometric parametric equation with defined coefficients
class ParametricEquation2d {
public:
    // param: x_a - coefficient for x parameter
    // param: y_b - coefficient for y parameter
    // param: scale - pixel scale of parametric graph
    ParametricEquation2d(double x_a, double y_b, int scale) : x_a(x_a), y_b(y_b), scale(scale) {}

    // Compute the point at parameter t (rounded to int)
    // param: t - the parameter value
    // return: SDL_FPoint - the computed point
    SDL_FPoint operator () (double t);

    // Generate a vector of points, evenly spaced on the parametric curve
    // param: num_points - the number of points to generate
    // param: t_offset - the offset from 0 of the points
    // param: join_ends - whether to join the first and last points
    // return: std::vector<SDL_FPoint> - the generated points
    std::vector<SDL_FPoint> gen_even_points(int num_points, double t_offset = 0.0, bool join_ends = true);

    void set_coeffs(double x_coeff, double y_coeff) { x_a = x_coeff; y_b = y_coeff; }
    std::pair<double, double> get_coeffs() { return std::pair<double, double>{x_a, y_b}; }

private:
    double x_a;
    double y_b;
    double scale;
};