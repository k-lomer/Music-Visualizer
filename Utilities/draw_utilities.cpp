#include "draw_utilities.h"

#include <algorithm>
#include <cmath>
#include <iostream>

int distance(const SDL_Point& v_1, const SDL_Point& v_2) {
    return int(sqrt((std::pow(v_1.x - v_2.x, 2) + std::pow(v_1.y - v_2.y, 2))));
}

double distance(const SDL_FPoint& v_1, const SDL_FPoint& v_2) {
    return double(sqrt((std::pow(v_1.x - v_2.x, 2) + std::pow(v_1.y - v_2.y, 2))));
}

double angle(const SDL_Point& v_1, const SDL_Point& v_2) {
    return atan2(double(v_2.y - v_1.y), double(v_2.x - v_1.x));
}

double angle(const SDL_FPoint& v_1, const SDL_FPoint& v_2) {
    return atan2(double(v_2.y - v_1.y), double(v_2.x - v_1.x));
}

SDL_Point float_to_pixel_point(const SDL_FPoint& p) {
    return SDL_Point{ std::lround(p.x), std::lround(p.y) };
}

SDL_FPoint pixel_to_float_point(const SDL_Point& p) {
    return SDL_FPoint{ float(p.x), float(p.y) };
}

std::vector<SDL_Point> float_to_pixel_points(const std::vector<SDL_FPoint>& points) {
    std::vector<SDL_Point> ret(points.size());
    std::transform(points.cbegin(), points.cend(), ret.begin(), float_to_pixel_point);
    return ret;
}

// Convert a vector of points from pixel (int) to float
std::vector<SDL_FPoint> pixel_to_float_points(const std::vector<SDL_Point>& points) {
    std::vector<SDL_FPoint> ret(points.size());
    std::transform(points.cbegin(), points.cend(), ret.begin(), pixel_to_float_point);
    return ret;
}

SDL_FPoint translate_point(const SDL_FPoint & v, const SDL_FPoint & translation) {
    return SDL_FPoint{ v.x + translation.x, v.y + translation.y };
}

SDL_Point translate_point(const SDL_Point & v, const SDL_Point & translation) {
    return SDL_Point{ v.x + translation.x, v.y + translation.y };
}

std::vector<SDL_Point> translate(const std::vector<SDL_Point>& points, const SDL_Point & translation) {
    std::vector<SDL_Point> translated_points;
    for (const auto &point : points) {
        translated_points.push_back(SDL_Point{ point.x + translation.x, point.y + translation.y });
    }
    return translated_points;
}

std::vector<SDL_FPoint> translate(const std::vector<SDL_FPoint>& points, const SDL_FPoint & translation) {
    std::vector<SDL_FPoint> translated_points;
    for (const auto &point : points) {
        translated_points.push_back(SDL_FPoint{ point.x + translation.x, point.y + translation.y });
    }
    return translated_points;
}

std::vector<SDL_Point> rotate(const std::vector<SDL_Point>& points, const SDL_Point & centre, double radians) {
    std::vector<SDL_Point> rotated_points;

    for (const auto &point : points) {
        rotated_points.push_back(rotate_point(point, centre, radians));
    }
    return rotated_points;
}

std::vector<SDL_FPoint> rotate(const std::vector<SDL_FPoint>& points, const SDL_FPoint & centre, double radians) {
    std::vector<SDL_FPoint> rotated_points;

    for (const auto &point : points) {
        rotated_points.push_back(rotate_point(point, centre, radians));
    }
    return rotated_points;
}

std::vector<SDL_Point> scale(const std::vector<SDL_Point> & points, double scale_factor) {
    std::vector<SDL_Point> scaled_points;

    for (const auto & point : points) {
        scaled_points.push_back(SDL_Point{ int(scale_factor * double(point.x)), int(scale_factor * double(point.y)) });
    }
    return scaled_points;
}

std::vector<SDL_FPoint> scale(const std::vector<SDL_FPoint> & points, double scale_factor) {
    std::vector<SDL_FPoint> scaled_points;

    for (const auto & point : points) {
        scaled_points.push_back(SDL_FPoint{ float(scale_factor) * point.x, float(scale_factor) * point.y });
    }
    return scaled_points;
}

std::vector<SDL_Point> scale(const std::vector<SDL_Point> & points, double scale_factor, const SDL_Point& centre) {
    return translate(scale(translate(points, SDL_Point{ -centre.x, -centre.y }), scale_factor), centre);
}

std::vector<SDL_FPoint> scale(const std::vector<SDL_FPoint> & points, double scale_factor, const SDL_FPoint& centre) {
    return translate(scale(translate(points, SDL_FPoint{ -centre.x, -centre.y }), scale_factor), centre);
}

SDL_Point rotate_point(const SDL_Point &v, const SDL_Point &centre, double radians) {
    double c = cos(radians);
    double s = sin(radians);

    SDL_Point offset = { v.x - centre.x, v.y - centre.y };
    SDL_Point rotated = { int(double(offset.x) * c - double(offset.y) * s) , int(double(offset.x) * s + double(offset.y) * c) };
    return SDL_Point{ rotated.x + centre.x, rotated.y + centre.y };
}

SDL_FPoint rotate_point(const SDL_FPoint &v, const SDL_FPoint &centre, double radians) {
    float c = float(cos(radians));
    float s = float(sin(radians));

    SDL_FPoint offset = { v.x - centre.x, v.y - centre.y };
    SDL_FPoint rotated = {offset.x * c - offset.y * s, offset.x * s + offset.y * c};
    return SDL_FPoint{ rotated.x + centre.x, rotated.y + centre.y };
}

std::vector<SDL_Point> interpolate_line(const SDL_Point & v_1, const SDL_Point & v_2, int num_points) {
    std::vector<SDL_Point> line_points{ v_1 };
    if (num_points > 2) {
        double x = double(v_1.x);
        double y = double(v_1.y);
        double x_step = double(v_2.x - v_1.x) / double(num_points - 1);
        double y_step = double(v_2.y - v_1.y) / double(num_points - 1);
        for (int i = 0; i < num_points - 2; ++i) {
            x += x_step;
            y += y_step;
            line_points.push_back(SDL_Point{ int(x), int(y) });
        }
    }
    line_points.push_back(v_2);

    return line_points;
}

SDL_Point point_on_line(const SDL_Point & v_1, const SDL_Point & v_2, double position) {
    return { int(v_1.x * (1.0 - position) + v_2.x * position), int(v_1.y * (1.0 - position) + v_2.y * position) };
}


std::vector<SDL_Point> gen_wave_points(std::vector<float> wave, int length, int amplitude) {
    // Handle silent/empty wave
    if (wave.empty()) {
        return std::vector<SDL_Point>{SDL_Point{ 0,0 }, SDL_Point{ length, 0 }};
    }
    
    double wave_step = wave.size() < length ? 1.0 : double(wave.size()) / double(length);
    double point_step = wave.size() > length ? 1.0 : double(length) / double(wave.size());

    double wave_pos = 0.0;
    double point_pos = 0.0;
    std::vector<SDL_Point> wave_points;
    while (wave_pos < double(wave.size()) && point_pos < double(length)) {
        int x = int(point_pos);
        int y = int(wave[int(wave_pos)] * float(amplitude));
        wave_points.push_back(SDL_Point{ x, y });

        wave_pos += wave_step;
        point_pos += point_step;
    }

    return wave_points;
}


void draw_circle(SDL_Renderer * const renderer, const SDL_Point & centre, int radius, const SDL_Color & color, int thickness) {
    std::vector<SDL_Point> perimeter(bresenhams_circle_points(radius));
    std::vector<SDL_Point> fill_points;

    if (thickness <= 0 || thickness >= radius) { // fill
        for (int i = 0; i < perimeter.size(); ++i) {
            fill_points.push_back(perimeter[i]);
            fill_points.push_back(SDL_Point{ -perimeter[i].x, perimeter[i].y });
        }
        for (int i = int(perimeter.size()) - 1; i >= 0; --i) {
            fill_points.push_back(SDL_Point{ perimeter[i].y, perimeter[i].x });
            fill_points.push_back(SDL_Point{ -perimeter[i].y, perimeter[i].x });
        }
        for (int i = 0; i < perimeter.size(); ++i) {
            fill_points.push_back(SDL_Point{ perimeter[i].y, -perimeter[i].x });
            fill_points.push_back(SDL_Point{ -perimeter[i].y, -perimeter[i].x });
        }
        for (int i = int(perimeter.size()) - 1; i >= 0; --i) {
            fill_points.push_back(SDL_Point{ perimeter[i].x, -perimeter[i].y });
            fill_points.push_back(SDL_Point{ -perimeter[i].x, -perimeter[i].y });
        }
    }
    else if (thickness == 1) { // outline only
        fill_points = std::move(perimeter);
        fill_points.push_back(fill_points[0]);
    }
    else { // thick line
        // This is the hardest case. We try to draw the right half of the circle first, then the left half
        std::vector<SDL_Point> inner_perimeter(bresenhams_circle_points(radius - thickness));
        std::vector<SDL_Point> inner_points;
        int y = perimeter[0].y;
        for (; y > inner_perimeter[0].y; --y) {
            inner_points.push_back(SDL_Point{ 0, y });
        }

        for (const auto& point : inner_perimeter) {
            if (y < 0) {
                break;
            }
            else if (point.y > y) {
                continue;
            }
            else {
                inner_points.push_back(point);
                --y;
            }
        }

        std::vector<SDL_Point> outer_points;
        outer_points.push_back(perimeter[0]);
        y = perimeter[0].y;
        for (int i = 0; i < perimeter.size(); ++i) {
            if (perimeter[i].y == y) {
                outer_points.back() = perimeter[i];
            }
            else {
                outer_points.push_back(perimeter[i]);
                --y;
            }
            if (y < 0) {
                break;
            }
        }
        
        // Generate points for the ring
        for (int i = 0; i < inner_points.size(); ++i) {
            fill_points.push_back(inner_points[i]);
            fill_points.push_back(outer_points[i]);
        }
        for (int i = int(inner_points.size()) - 1; i >= 0; --i) {
            fill_points.push_back(SDL_Point{ inner_points[i].x, -inner_points[i].y });
            fill_points.push_back(SDL_Point{ outer_points[i].x, -outer_points[i].y });
        }
        std::cout << std::endl;
        for (int i = 0; i < inner_points.size(); ++i) {
            fill_points.push_back(SDL_Point{ -inner_points[i].x, -inner_points[i].y });
            fill_points.push_back(SDL_Point{ -outer_points[i].x, -outer_points[i].y });
        }
        for (int i = int(inner_points.size()) - 1; i >= 0; --i) {
            fill_points.push_back(SDL_Point{ -inner_points[i].x, inner_points[i].y });
            fill_points.push_back(SDL_Point{ -outer_points[i].x, outer_points[i].y });
        }
    }

    fill_points = translate(fill_points, centre);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLines(renderer, &fill_points[0], (int)fill_points.size());
}

std::vector<SDL_Point> bresenhams_circle_points(int r) {
    std::vector<SDL_Point> points;
    int x = 0;
    int y = r;
    int d = 3 - (2 * r);

    while (x <= y) {
        points.push_back(SDL_Point{ x, y });
        ++x;
        if (d < 0) {
            d = d + (4 * x) + 6;
        }
        else {
            d = d + 4 * (x - y) + 10;
            --y;
        }
    }

    int eighth_point_count = int(points.size());

    for (int i = eighth_point_count - 1; i >= 0; --i)
        points.push_back(SDL_Point{ points[i].y, points[i].x });
    for (int i = 0; i < eighth_point_count; ++i)
        points.push_back(SDL_Point{ points[i].y, -points[i].x });
    for (int i = eighth_point_count - 1; i >= 0; --i)
        points.push_back(SDL_Point{ points[i].x, -points[i].y });
    for (int i = 0; i < eighth_point_count; ++i)
        points.push_back(SDL_Point{ -points[i].x, -points[i].y });
    for (int i = eighth_point_count - 1; i >= 0; --i)
        points.push_back(SDL_Point{ -points[i].y, -points[i].x });
    for (int i = 0; i < eighth_point_count; ++i)
        points.push_back(SDL_Point{ -points[i].y, points[i].x });
    for (int i = eighth_point_count - 1; i >= 0; --i)
        points.push_back(SDL_Point{ -points[i].x, points[i].y });


    return points;
}

void draw_wave(SDL_Renderer * const renderer, const std::vector<float> &wave, const SDL_Point &start, const SDL_Point & end, int amplitude, const SDL_Color& color) {
    int length = distance(start, end);
    if (length == 0) { return; }

    std::vector<SDL_Point> wave_points = gen_wave_points(wave, length, -amplitude);
    // move to correct start and end points
    wave_points = translate(wave_points, start);
    wave_points = rotate(wave_points, start, angle(start, end));

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLines(renderer, &wave_points[0], (int)wave_points.size());
}

void draw_wave_fill(SDL_Renderer * const renderer, const std::vector<float> &wave, const SDL_Point &start, const SDL_Point & end, int amplitude, const SDL_Color& color) {
    std::vector<SDL_Point> fill_points;
    int length = distance(start, end);
    if (length == 0) { 
        fill_points = std::vector<SDL_Point>{start, end};
    }
    else {
        std::vector<SDL_Point> wave_points = gen_wave_points(wave, length, -amplitude);
        for (int i = 0; i < wave_points.size() - 1; ++i) {
            // generate column points in the polygon between two wave points
            SDL_Point w_1 = wave_points[i];
            SDL_Point w_2 = wave_points[i + 1];
            auto polygon_points = interpolate_line(w_1, w_2, abs(w_2.x - w_1.x) + 1);
            for (int j = 0; j < polygon_points.size() - 1; ++j) {
                fill_points.push_back(SDL_Point{ polygon_points[j].x, 0 });
                fill_points.push_back(SDL_Point{ polygon_points[j] });
                fill_points.push_back(SDL_Point{ polygon_points[j].x, 0 });
            }
        }

        fill_points = translate(fill_points, start);
        fill_points = rotate(fill_points, start, angle(start, end));
    }
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLines(renderer, &fill_points[0], (int)fill_points.size());
}


void draw_bars(SDL_Renderer * const renderer, const std::vector<float> &bar_values, const SDL_Point &start, const SDL_Point & end, int amplitude, const SDL_Color& color) {
    int length = distance(start, end);
    if (length == 0) { return; }
    std::vector<SDL_Point> bar_heights = gen_wave_points(bar_values, length, -amplitude);

    // move to correct start and end points
    std::vector<SDL_Point> bar_midpoints = translate(bar_heights, start);
    bar_midpoints = rotate(bar_midpoints, start, angle(start, end));

    int min_bar_width = abs(end.x - start.x) / (int)bar_values.size();
    // account for total length not divisible by number of bars
    int pixel_remainder = abs(end.x - start.x) % bar_values.size();

    std::vector<SDL_Rect> bars;
    int x_pos = start.x;
    for (int i = 0; i < bar_values.size(); ++i) {
        int bar_width = min_bar_width + (i < pixel_remainder ? 1 : 0);
        bars.push_back(SDL_Rect{ x_pos, bar_midpoints[i].y - bar_heights[i].y, bar_width, bar_heights[i].y });
        x_pos += bar_width;
    }
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRects(renderer, &bars[0], (int)bars.size());

}

