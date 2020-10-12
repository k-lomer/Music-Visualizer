#pragma once

#include "visual_layer.h"

// a wave between two points, can have multiple layers of differing amplitudes
class WaveLayer : public VisualLayer {
public:
    // param: num_waves - the number of waves to draw
    // param: wave_start - the coordinates of the start of the waves
    // param: wave_end - the coordinates of the end of the waves
    // param: wave_amplitude - the the maximum pixel amplitude of the waves
    // param: wave_color - the color of the waves
    WaveLayer(int num_waves, SDL_Point wave_start, SDL_Point wave_end, int wave_amplitude, SDL_Color wave_color)
        : wave_count(num_waves), start(wave_start), end(wave_end), amplitude(wave_amplitude), color(wave_color) {}

    virtual void draw(SDL_Renderer * renderer, const packet & packet_buffer) override;

private:
    int wave_count;
    SDL_Point start;
    SDL_Point end;
    int amplitude;
    SDL_Color color;
};
