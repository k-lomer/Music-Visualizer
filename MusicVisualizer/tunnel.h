#pragma once

#include "composite_layer.h"

// A tunnel of boxes fitting the window
class TunnelLayer : public virtual CompositeLayer {
public:
    // param: window_width - the pixel width of the window
    // param: window_height - the pixel height of the window
    // param: levels - the number of boxes to draw
    TunnelLayer(int width, int height, int num_waves, int levels, int wave_amplitude, SDL_Color wave_color, double box_scale_rate);

    virtual void draw(SDL_Renderer * const renderer, const wave & signal) override;

private:
    int window_width;
    int window_height;
    int wave_count;
    int amplitude;
    SDL_Color color;
    double scale_rate;
    double scale_difference;
};
