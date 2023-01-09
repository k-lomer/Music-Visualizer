#include "wave_layer.h"

#include "../Utilities/draw_utilities.h"

void WaveLayer::draw(SDL_Renderer * const renderer, const wave & signal) {
    m_rotation += m_rotation_rate;
    if (m_rotation > 2 * M_PI) {
        m_rotation -= 2 * M_PI;
    }
    else if (m_rotation < 0.0) {
        m_rotation += 2 * M_PI;
    }
    
    SDL_Point rotated_start = rotate_point(m_start, m_centre, m_rotation);
    SDL_Point rotated_end = rotate_point(m_end, m_centre, m_rotation);

    for (int i = m_wave_count; i > 0; --i) {
        int wave_amplitude = int(m_amplitude * i / m_wave_count);
        draw_wave(renderer, signal, rotated_start, rotated_end, wave_amplitude, m_color);
    }
    for (int i = m_wave_count; i > 0; --i) {
        int wave_amplitude = -int(m_amplitude * i / m_wave_count);
        draw_wave(renderer, signal, rotated_start, rotated_end, wave_amplitude, m_color);
    }
}
