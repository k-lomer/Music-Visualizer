#pragma once

#include "visual_layer.h"

// A rectangle of waves along the edge of the window
class ScreenBoxLayer : public VisualLayer {
public:
    // param: num_waves - the number of waves to draw
    // param: width - the width of the window
    // param: height - the height of the window
    // param: wave_amplitude - the maximum pixel amplitude of the waves
    // param: wave_color - the color of the waves
    ScreenBoxLayer(int num_waves, int width, int height, int wave_amplitude, SDL_Color wave_color)
        : wave_count(num_waves), window_width(width), window_height(height), amplitude(wave_amplitude), color(wave_color) {}

    virtual void draw(SDL_Renderer * renderer, const SignalBox & signal_box) override;

private:
    int wave_count;
    int window_width;
    int window_height;
    int amplitude;
    SDL_Color color;
};

