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
    UnknownPleasureLayer(int num_waves, int frame_delay, SDL_Point first_wave_start, SDL_Point first_wave_end,
        SDL_Point last_wave_start, SDL_Point last_wave_end, int wave_amplitude, SDL_Color wave_color);

    virtual void draw(SDL_Renderer * renderer, const SignalBox & signal_box) override;

private:
    int wave_count;
    int delay;
    SDL_Point front_start;
    SDL_Point front_end;
    SDL_Point back_start;
    SDL_Point back_end;
    int amplitude;
    SDL_Color color;
    std::deque<std::vector<float>> waveforms;
};
