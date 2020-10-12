#pragma once

#include "visual_layer.h"
#include <vector>

// A series of waves which move across the screen horizontally or vertically
class MovingWaveLayer : public VisualLayer {
public:
    // param: num_waves - the number of waves on the screen at any time
    // param: wave_orientation - whether the waves are horizontal or vertical
    // param: wave_movement - the per pixel movement at each update
    // param: width - the width of the screen
    // param: height - the height of the screen
    // param: wave_amplitude - the maximum amplitude of the waves in pixels
    // param: wave_color - the color of the waves
    MovingWaveLayer(int num_waves, orientation wave_orientation, double wave_movement, int width, int height, int wave_amplitude, SDL_Color wave_color);


    virtual void draw(SDL_Renderer * renderer, const packet & packet_buffer) override;

private:
    orientation wave_orientation;
    double movement;
    int window_width;
    int window_height;
    int amplitude;
    SDL_Color color;
    // the current positions of waves in given orientation
    std::vector<double> wave_positions;
};
