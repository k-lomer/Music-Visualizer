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
        : m_wave_count(num_waves), m_window_width(width), m_window_height(height), m_amplitude(wave_amplitude), m_color(wave_color), m_scale(box_scale), m_scale_rate(box_scale_rate){}

    // Draw the ScreenBoxLayer.
    // param: renderer                      - the renderer to draw the ScreenBoxLayer
    // param: signal                        - the signal to draw
    virtual void draw(SDL_Renderer * renderer, const wave & signal) override;

    double get_scale() const { return m_scale; }

private:
    // The number of waves to draw.
    int m_wave_count;
    // The width of the window.
    int m_window_width;
    // The height of the window.
    int m_window_height;
    // The maximum amplitude of waves.
    int m_amplitude;
    // The color to draw waves.
    SDL_Color m_color;
    // The scale of the box, about the centre of the window.
    double m_scale;
    // The rate at which to scale the box.
    double m_scale_rate;
};

