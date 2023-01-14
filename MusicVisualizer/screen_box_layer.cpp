#include "screen_box_layer.h"

#include "../Utilities/draw_utilities.h"

void ScreenBoxLayer::draw(SDL_Renderer * const renderer, const wave & signal) {
    m_scale += m_scale_rate;
    if (m_scale <= 0.0) {
        return;
    }

    SDL_Point centre{ m_window_width / 2, m_window_height / 2 };
    // Use width/height - 1 so the stationary line is visible.
    SDL_Point tl = { int((1.0 - m_scale) * double(centre.x)), int((1.0 - m_scale) * double(centre.y)) };
    SDL_Point tr = { (m_window_width - 1) - int((1.0 - m_scale) * double(centre.x)), int((1.0 - m_scale) * double(centre.y)) };
    SDL_Point bl = { int((1.0 - m_scale) * double(centre.x)) , (m_window_height - 1) - int((1.0 - m_scale) * double(centre.y)) };
    SDL_Point br = { (m_window_width - 1) - int((1.0 - m_scale) * double(centre.x)) , (m_window_height - 1) - int((1.0 - m_scale) * double(centre.y)) };

    for (int i = m_wave_count; i >= 0; --i) {
        int wave_amplitude = (i == 0 ? 0 : int(m_amplitude * i / m_wave_count));
        draw_wave(renderer, signal, tl, bl, -wave_amplitude, m_color);
        draw_wave(renderer, signal, bl, br, -wave_amplitude, m_color);
        draw_wave(renderer, signal, br, tr, -wave_amplitude, m_color);
        draw_wave(renderer, signal, tr, tl, -wave_amplitude, m_color);
    }
}
