#pragma once

#include "visual_layer.h"

// A rectangle of waves along the edges of the window.
class ScreenBoxLayer : public VisualLayer {
public:
    // ScreenBoxLayer constructor.
    // param: num_waves                     - the number of waves to draw
    // param: width                         - the width of the window
    // param: height                        - the height of the window
    // param: wave_amplitude                - the maximum pixel amplitude of the waves
    // param: wave_color                    - the color of the waves
    // param: box_scale                     - the scale of the box
    // param: box_scale_rate                - the rate at which to scale the box
    ScreenBoxLayer(int num_waves, int width, int height, int wave_amplitude, SDL_Color wave_color, double box_scale = 1.0, double box_scale_rate = 0.0)
        : wave_count(num_waves), window_width(width), window_height(height), amplitude(wave_amplitude), color(wave_color), scale(box_scale), scale_rate(box_scale_rate){}

    // Draw the ScreenBoxLayer.
    // param: renderer                      - the renderer to draw the ScreenBoxLayer
    // param: signal                        - the signal to draw
    virtual void draw(SDL_Renderer * renderer, const wave & signal) override;

    double get_scale() const { return scale; }

private:
    // The number of waves to draw.
    int wave_count;
    // The width of the window.
    int window_width;
    // The height of the window.
    int window_height;
    // The maximum amplitude of waves.
    int amplitude;
    // The color to draw waves.
    SDL_Color color;
    // The scale of the box, about the centre of the window.
    double scale;
    // The rate at which to scale the box.
    double scale_rate;
};

