#include "moving_wave_layer.h"

#include <algorithm>

#include "../Utilities/draw_utilities.h"

MovingWaveLayer::MovingWaveLayer(int num_waves, Orientation wave_orientation, double wave_movement, int width, int height, int wave_amplitude, SDL_Color wave_color)
    : m_wave_orientation(wave_orientation), m_movement(wave_movement), m_window_width(width), m_window_height(height), m_amplitude(wave_amplitude), m_color(wave_color) {
    // Use num_waves + 1 for a smooth transition on/off screen.
    for (int i = 0; i < num_waves + 1; ++i) {
        int length = wave_orientation == Horizontal ? height : width;
            m_wave_positions.push_back(double(length) * double(i) / double(num_waves) + double(length) / (2 * double(num_waves)));
    }
}

// This is made trickier than it should be to ensure a smooth transition (wraparound) between waves.
// There is always an extra wave that only becomes visible as the previous one leaves the screen.
void MovingWaveLayer::draw(SDL_Renderer * renderer, const wave & signal) {
    int length = m_wave_orientation == Horizontal ? m_window_height : m_window_width;
    int visible_waves = (int)m_wave_positions.size() - 1;
    // Move wave positions and wrap around waves which are off the screen.
    for (double & pos : m_wave_positions) {
        pos += m_movement;
        if (m_movement > 0 && pos > length + length / visible_waves) {
            pos -= length + length / visible_waves;
        }
        else if (m_movement < 0 && pos < -length / visible_waves) {
            pos += length + length / visible_waves;
        }
    }

    for (double pos : m_wave_positions) {
        if (m_wave_orientation == Horizontal) {
            draw_wave(renderer, signal, SDL_Point{0, int(pos)}, SDL_Point{m_window_width, int(pos) }, m_amplitude, m_color);
        }
        else {
            draw_wave(renderer, signal, SDL_Point{ int(pos), 0}, SDL_Point{ int(pos), m_window_height }, m_amplitude, m_color);
        }
    }

}
