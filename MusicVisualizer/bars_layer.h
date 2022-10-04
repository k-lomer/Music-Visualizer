#pragma once

#pragma once

#include "visual_layer.h"

// a wave between two points, can have multiple layers of differing amplitudes
class BarsLayer : public VisualLayer {
public:
    // param: divisions - the number of bars to draw
    // param: bars_start - the coordinates of the start of the bars
    // param: bars_end - the coordinates of the end of the bars
    // param: bars_amplitude - the the maximum pixel amplitude of the bars
    // param: bars_color - the color of the bars
    BarsLayer(int num_bars, SDL_Point bars_start, SDL_Point bars_end, int bars_amplitude, SDL_Color bars_color)
        : divisions(num_bars), start(bars_start), end(bars_end), amplitude(bars_amplitude), color(bars_color) {}

    virtual void draw(SDL_Renderer * renderer, const wave & signal) override;

private:
    int divisions;
    SDL_Point start;
    SDL_Point end;
    int amplitude;
    SDL_Color color;
};
