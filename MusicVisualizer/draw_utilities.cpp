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


void draw_circle(SDL_Renderer * const renderer, const SDL_Point &centre, int radius, const SDL_Color& color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    for (int x = centre.x - radius; x <= centre.x + radius; x++) {
        for (int y = centre.y - radius; y <= centre.y + radius; y++) {
            if ((std::pow(centre.y - y, 2) + std::pow(centre.x - x, 2)) <=
                std::pow(radius, 2)) {
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
}

void draw_wave(SDL_Renderer * const renderer, const std::vector<float> &wave, const SDL_Point &start, const SDL_Point & end, int amplitude, const SDL_Color& color) {
    int length = distance(start, end);
    if (length == 0) { return; }
    std::vector<SDL_Point> wave_points = gen_wave_points(wave, length, amplitude);
    
    // move to correct start and end points
    wave_points = translate(wave_points, start);
    wave_points = rotate(wave_points, start, angle(start, end));

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLines(renderer, &wave_points[0], (int)wave_points.size());
}
