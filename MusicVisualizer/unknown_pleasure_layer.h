#pragma once

#include <deque>

#include "visual_layer.h"

// I've been waiting for a guide to come and take me by the hand.
// Could these sensations make me feel the pleasures of a normal man?
class UnknownPleasureLayer : public VisualLayer {
public:
    // Draw line waves with optional background fill
    // param: num_waves - the number of waves to draw
    // param: frame_delay - the number of frames of delay between each wave
    // param: first_wave_start - the coordinates of the start of the front wave
    // param: first_wave_end - the coordinates of the end of the front wave
    // param: last_wave_start - the coordinates of the start of the back wave
    // param: last_wave_end - the coordinates of the end of the back wave
    // param: wave_amplitude - the the maximum pixel amplitude of the waves
    // param: wave_color - the color of the waves
    // param: fill_waves - whether to fill the waves in a solid color
    UnknownPleasureLayer(int num_waves, int frame_delay, SDL_Point first_wave_start, SDL_Point first_wave_end,
        SDL_Point last_wave_start, SDL_Point last_wave_end, int wave_amplitude, const std::vector<SDL_Color> & wave_colors, bool fill_waves);

    // Draw different colored filled waves
    // param: num_waves - the number of waves to draw
    // param: frame_delay - the number of frames of delay between each wave
    // param: first_wave_start - the coordinates of the start of the front wave
    // param: first_wave_end - the coordinates of the end of the front wave
    // param: last_wave_start - the coordinates of the start of the back wave
    // param: last_wave_end - the coordinates of the end of the back wave
    // param: wave_amplitude - the the maximum pixel amplitude of the waves
    // param: fill_waves - whether to fill the waves in a solid color
    UnknownPleasureLayer(int num_waves, int frame_delay, SDL_Point first_wave_start, SDL_Point first_wave_end,
        SDL_Point last_wave_start, SDL_Point last_wave_end, int wave_amplitude, const std::vector<SDL_Color> & fill_colors);

    virtual void draw(SDL_Renderer * renderer, const wave & signal) override;

private:
    int wave_count;
    int delay;
    SDL_Point front_start;
    SDL_Point front_end;
    SDL_Point back_start;
    SDL_Point back_end;
    int amplitude;
    std::vector<SDL_Color> line_colors;
    std::deque<std::vector<float>> waveforms;
    std::vector<SDL_Color> fill_colors;
};
