#include "unknown_pleasure_layer.h"

#include "../Utilities/draw_utilities.h"

UnknownPleasureLayer::UnknownPleasureLayer(int num_waves, int frame_delay, SDL_Point first_wave_start, SDL_Point first_wave_end,
    SDL_Point last_wave_start, SDL_Point last_wave_end, int wave_amplitude, const std::vector<SDL_Color> & wave_colors, UnknownPleasureFill fill_waves)
    : m_wave_count(num_waves), m_delay(frame_delay), m_front_start(first_wave_start), m_front_end(first_wave_end),
    m_back_start(last_wave_start), m_back_end(last_wave_end), m_amplitude(wave_amplitude), m_line_colors()
{
    set_precedence(-10);

    for (int i = 0; i < m_wave_count * m_delay + 1; ++i) {
        m_waveforms.emplace_back();
    }

    switch (fill_waves) {
    case UnknownPleasureFill::None: {
        m_line_colors = wave_colors;
        break;
    }
    case UnknownPleasureFill::Black: {
        m_line_colors = wave_colors;
        m_fill_colors.push_back(SDL_Color{ 0, 0, 0, SDL_ALPHA_OPAQUE });
        break;
    }
    case UnknownPleasureFill::Color: {
        m_line_colors.push_back(SDL_Color{ 0, 0, 0, SDL_ALPHA_OPAQUE });
        m_fill_colors = wave_colors;
        break;
    }
    }
}

void UnknownPleasureLayer::draw(SDL_Renderer * renderer, const wave & signal) {
    m_waveforms.push_front(signal);
    m_waveforms.pop_back();

    auto starts = interpolate_line(m_front_start, m_back_start, m_wave_count);
    auto ends = interpolate_line(m_front_end, m_back_end, m_wave_count);
    for (int i = int(starts.size()) - 1; i >= 0 ; --i) {
        if (!m_fill_colors.empty()) {
            draw_wave_fill(renderer, m_waveforms[i * m_delay], starts[i], ends[i], m_amplitude, m_fill_colors[i % m_fill_colors.size()]);
        }
        if (!m_line_colors.empty()) {
            draw_wave(renderer, m_waveforms[i * m_delay], starts[i], ends[i], m_amplitude, m_line_colors[i % m_line_colors.size()]);
        }
    }
}
