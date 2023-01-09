#pragma once

#include "parametric.h"

#include <deque>

#include "draw_utilities.h"


SDL_FPoint ParametricEquation2d::operator () (double t) const {
    return SDL_FPoint{ float(m_scale * cos(m_x_a * t)), float(m_scale * sin(m_y_b * t)) };
}

std::vector<SDL_FPoint> ParametricEquation2d::gen_even_points(int num_points, double t_span, double t_offset, bool join_points) const {
    double step =  t_span / double(num_points);
    std::deque<SDL_FPoint> points;
    int i = 0;
    // If joining the start and end point, keep generating points until they are suitably close (for aesthetics). 
    while (points.size() < num_points ||
        (join_points && (abs(points.front().x - points.back().x) > 0.5f || abs(points.front().y - points.back().y) > 0.5f))) {
        points.push_front(this->operator()(i * step + t_offset));
        points.push_back(this->operator()(-i * step + t_offset));
        ++i;
    }

    return std::vector<SDL_FPoint>(points.begin(), points.end());
}

