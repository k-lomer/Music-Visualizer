#pragma once

#include <deque>

#include "visual_layer.h"

// I've been waiting for a guide to come and take me by the hand.
// Could these sensations make me feel the pleasures of a normal man?
// Draw wave line waves with optional background fill.
class UnknownPleasureLayer : public VisualLayer {
public:
    // Enum representing the different layer fill types.
    enum UnknownPleasureFill {
        None,
        Black,
        Color
    };
    // UnknownPleasureLayer constructor.
    // param: num_waves                     - the number of waves to draw
    // param: frame_delay                   - the number of frames of delay between each wave
    // param: first_wave_start              - the coordinates of the start of the front wave
    // param: first_wave_end                - the coordinates of the end of the front wave
    // param: last_wave_start               - the coordinates of the start of the back wave
    // param: last_wave_end                 - the coordinates of the end of the back wave
    // param: wave_amplitude                - the the maximum pixel amplitude of the waves
    // param: wave_color                    - the color of the waves
    // param: fill_waves                    - how to fill the waves
    UnknownPleasureLayer(int num_waves, int frame_delay, SDL_Point first_wave_start, SDL_Point first_wave_end,
        SDL_Point last_wave_start, SDL_Point last_wave_end, int wave_amplitude, const std::vector<SDL_Color> & wave_colors, UnknownPleasureFill fill_waves);

    // Draw the UnknownPleasureLayer.
    // param: renderer                      - the renderer to draw the UnknownPleasureLayer
    // param: signal                        - the signal to draw
    virtual void draw(SDL_Renderer * renderer, const wave & signal) override;

private:
    // The number of waves to draw.
    int m_wave_count;
    // The number of frames of delay between each wave.
    int m_delay;
    // The coordinates of the start of the front wave.
    SDL_Point m_front_start;
    // The coordinates of the end of the front wave.
    SDL_Point m_front_end;
    // The coordinates of the start of the back wave.
    SDL_Point m_back_start;
    // The coordinates of the end of the back wave.
    SDL_Point m_back_end;
    // The maximum aplitude of the waves.
    int m_amplitude;
    // The colors to draw the waves.
    std::vector<SDL_Color> m_line_colors;
    // The different waves to draw.
    std::deque<std::vector<float>> m_waveforms;
    // The colors to fill the waves.
    std::vector<SDL_Color> m_fill_colors;
};
