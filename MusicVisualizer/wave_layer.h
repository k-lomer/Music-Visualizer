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
    // param: init_rotation - the initial rotation of the wave
    // param: rotation_rate - the rate of rotation of the wave
    WaveLayer(int num_waves, SDL_Point wave_start, SDL_Point wave_end, int wave_amplitude, SDL_Color wave_color, double init_rotation = 0.0, double rotation_rate = 0.0)
        : wave_count(num_waves), start(wave_start), end(wave_end), amplitude(wave_amplitude), color(wave_color), rotation(init_rotation), rotation_rate(rotation_rate)
    {
        centre = SDL_Point{ (start.x + end.x) / 2, (start.y + end.y) / 2 };
    }

    virtual void draw(SDL_Renderer * renderer, const SignalBox & signal_box) override;

private:
    int wave_count;
    SDL_Point start;
    SDL_Point end;
    SDL_Point centre;
    int amplitude;
    SDL_Color color;
    double rotation;
    double rotation_rate;
};
