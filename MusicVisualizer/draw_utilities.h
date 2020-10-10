#pragma once

#include <vector>

#include "SDL.h"

int distance(const SDL_Point& v_1, const SDL_Point& v_2);

double angle(const SDL_Point& v_1, const SDL_Point& v_2);

void translate(std::vector<SDL_Point>& points, const SDL_Point & translation);

SDL_Point rotate_point(const SDL_Point &v, const SDL_Point &centre, double radians);

void rotate(std::vector<SDL_Point>& points, const SDL_Point & centre, double radians);

SDL_Point rotate_point(const SDL_Point &v, const SDL_Point &centre, double rad);

std::vector<SDL_Point> gen_wave_points(std::vector<float> wave, int length, int amplitude);

void draw_circle(SDL_Renderer * const renderer, const SDL_Point &centre, int radius, const SDL_Color& color);

void draw_wave(SDL_Renderer * const renderer, const std::vector<float> &wave, const SDL_Point &start, const SDL_Point & end, int amplitude, const SDL_Color& color);
