#include "draw_utilities.h"

#include <cmath>

int distance(const SDL_Point& v_1, const SDL_Point& v_2) {
    return int(sqrt((std::pow(v_1.x - v_2.x, 2) + std::pow(v_1.y - v_2.y, 2))));
}

double angle(const SDL_Point& v_1, const SDL_Point& v_2) {
    return atan2(double(v_2.y - v_1.y), double(v_2.x - v_1.x));
}

std::vector<SDL_Point> translate(const std::vector<SDL_Point>& points, const SDL_Point & translation) {
    std::vector<SDL_Point> translated_points;
    for (const auto &point : points) {
        translated_points.push_back(SDL_Point{ point.x + translation.x, point.y + translation.y });
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

SDL_Point rotate_point(const SDL_Point &v, const SDL_Point &centre, double radians) {
    double c = cos(radians);
    double s = sin(radians);

    SDL_Point offset = { v.x - centre.x, v.y - centre.y };
    SDL_Point rotated = { int(double(offset.x) * c - double(offset.y) * s) , int(double(offset.x) * s + double(offset.y) * c) };
    return SDL_Point{ rotated.x + centre.x, rotated.y + centre.y };
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

// This implementation works by computing the height at which the width of the circle changes and filling that space with lines
// For rotational symmetry we plot the same for width and height reversed
// This could be more efficient but it works well enough for now
void draw_circle(SDL_Renderer * const renderer, const SDL_Point &centre, int radius, const SDL_Color& color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    
    int radius_squared = radius * radius;
    int previous_offset_2 = radius+1;
    for (int offset_1 = 0; offset_1 <= radius; ++offset_1) {
        int new_offset_2 = (int)sqrt(double(radius_squared - offset_1 * offset_1));
        for (int offset_2 = new_offset_2; offset_2 <= previous_offset_2; ++offset_2) {
            // aply offsets horizontally
            SDL_RenderDrawLine(renderer, centre.x + offset_1, centre.y + offset_2, centre.x - offset_1, centre.y + offset_2);
            SDL_RenderDrawLine(renderer, centre.x + offset_1, centre.y - offset_2, centre.x - offset_1, centre.y - offset_2);
            // apply offsets vertically for symmetry
            SDL_RenderDrawLine(renderer, centre.x - offset_2, centre.y + offset_1, centre.x - offset_2, centre.y - offset_1);
            SDL_RenderDrawLine(renderer, centre.x + offset_2, centre.y + offset_1, centre.x + offset_2, centre.y - offset_1);

        }
        previous_offset_2 = new_offset_2;

    }
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

