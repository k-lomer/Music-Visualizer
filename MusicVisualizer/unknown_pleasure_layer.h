#pragma once

#include <deque>

#include "visual_layer.h"

// I've been waiting for a guide to come and take me by the hand.
// Could these sensations make me feel the pleasures of a normal man?
class UnknownPleasureLayer : public VisualLayer {
public:
    // param: num_waves - the number of waves to draw
    // param: wave_start - the coordinates of the start of the waves
    // param: wave_end - the coordinates of the end of the waves
    // param: wave_amplitude - the the maximum pixel amplitude of the waves
    // param: wave_color - the color of the waves
    UnknownPleasureLayer(int num_waves, SDL_Point first_wave_start, SDL_Point first_wave_end, SDL_Point last_wave_start, SDL_Point last_wave_end, int wave_amplitude, SDL_Color wave_color)
        : wave_count(num_waves), front_start(first_wave_start), front_end(first_wave_end),
        back_start(last_wave_start), back_end(last_wave_end), amplitude(wave_amplitude), color(wave_color)
    {
        for (int i = 0; i < num_waves; ++i) {
            waveforms.emplace_back();
        }
    }

    virtual void draw(SDL_Renderer * renderer, const SignalBox & signal_box) override;

private:
    int wave_count;
    SDL_Point front_start;
    SDL_Point front_end;
    SDL_Point back_start;
    SDL_Point back_end;
    int amplitude;
    SDL_Color color;
    std::deque<std::vector<float>> waveforms;
};
