#pragma once

#include "visual_layer.h"

// A wave between two points, can have multiple layers of differing amplitudes.
class WaveLayer : public VisualLayer {
public:
    // WaveLayer constructor.
    // param: num_waves                     - the number of waves to draw
    // param: wave_start                    - the coordinates of the start of the waves
    // param: wave_end                      - the coordinates of the end of the waves
    // param: wave_amplitude                - the the maximum pixel amplitude of the waves
    // param: wave_color                    - the color of the waves
    // param: init_rotation                 - the initial rotation of the wave
    // param: rotation_rate                 - the rate of rotation of the wave
    WaveLayer(int num_waves, SDL_Point wave_start, SDL_Point wave_end, int wave_amplitude, SDL_Color wave_color, double init_rotation = 0.0, double rotation_rate = 0.0)
        : m_wave_count(num_waves), m_start(wave_start), m_end(wave_end), m_amplitude(wave_amplitude), m_color(wave_color), m_rotation(init_rotation), m_rotation_rate(rotation_rate)
    {
        m_centre = SDL_Point{ (m_start.x + m_end.x) / 2, (m_start.y + m_end.y) / 2 };
    }

    // Draw the WaveLayer.
    // param: renderer                      - the renderer to draw the WaveLayer
    // param: signal                        - the signal to draw
    virtual void draw(SDL_Renderer * renderer, const wave & signal) override;

private:
    // The number of waves to draw.
    int m_wave_count;
    // The start of the wave.
    SDL_Point m_start;
    // The end of the wave.
    SDL_Point m_end;
    // The centre of rotation.
    SDL_Point m_centre;
    // The maximum wave amplitude in pixels.
    int m_amplitude;
    // The color of the wave.
    SDL_Color m_color;
    // The current rotation of the wave.
    double m_rotation;
    // The number of radians the wave is rotated each time it is drawn.
    double m_rotation_rate;
};
