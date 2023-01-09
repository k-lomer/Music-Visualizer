#pragma once

#include "visual_layer.h"
#include <vector>

// A series of waves which move across the screen horizontally or vertically.
class MovingWaveLayer : public VisualLayer {
public:
    // MovingWaveLayer constructor.
    // param: num_waves                         - the number of waves on the screen at any time
    // param: wave_orientation                  - whether the waves are horizontal or vertical
    // param: wave_movement                     - the per pixel movement at each update
    // param: width                             - the width of the screen
    // param: height                            - the height of the screen
    // param: wave_amplitude                    - the maximum amplitude of the waves in pixels
    // param: wave_color                        - the color of the waves
    MovingWaveLayer(int num_waves, Orientation wave_orientation, double wave_movement, int width, int height, int wave_amplitude, SDL_Color wave_color);

    // Draw the MovingWaveLayer.
    // param: renderer                          - the renderer to draw the MovingWaveLayer
    // param: signal                            - the signal to draw
    virtual void draw(SDL_Renderer * renderer, const wave & signal) override;

private:
    // The orientation of the waves.
    Orientation wave_orientation;
    // The per pixel movement at each update.
    double movement;
    // The window width.
    int window_width;
    // The window height.
    int window_height;
    // The maximum amplitude of the waves.
    int amplitude;
    // The color of the waves.
    SDL_Color color;
    // The current positions of waves in given orientation.
    std::vector<double> wave_positions;
};
