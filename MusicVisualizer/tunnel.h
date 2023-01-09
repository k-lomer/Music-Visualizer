#pragma once

#include "composite_layer.h"

// A tunnel of boxes fitting the window, whose sides are sound waves.
class TunnelLayer : public virtual CompositeLayer {
public:
    // TunnelLayer Constructor.
    // param: width                     - the pixel width of the window
    // param: height                    - the pixel height of the window
    // param: levels                    - the number of boxes to draw
    // param: wave_amplitude            - the maximum amplitude of the waves
    // param: wave_color                - the color of the waves
    // param: box_scale_rate            - the rate at which the tunnels change scale.
    TunnelLayer(int width, int height, int num_waves, int levels, int wave_amplitude, SDL_Color wave_color, double box_scale_rate);

    // Draw the TunnelLayer.
    // param: renderer                  - the renderer to draw the TunnelLayer
    // param: signal                    - the signal to draw
    virtual void draw(SDL_Renderer * const renderer, const wave & signal) override;

private:
    // The width of the window.
    int m_window_width;
    // The height of the window.
    int m_window_height;
    // The number of waves to draw of the side of each box.
    int m_wave_count;
    // The maximum amplitude of the waves.
    int m_amplitude;
    // The color to draw the waves.
    SDL_Color m_color;
    // The scale rate of the boxes.
    double m_scale_rate;
    // The difference in scale between the boxes.
    double m_scale_difference;
};
