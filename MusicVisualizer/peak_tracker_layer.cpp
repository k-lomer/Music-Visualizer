#include "peak_tracker_layer.h"

#include "../Utilities/draw_utilities.h"

PeakTrackerLayer::PeakTrackerLayer(int num_peaks, int window_width, int window_height, SDL_Color peak_color)
    : m_peaks(num_peaks), m_window_width(window_width), m_window_height(window_height), m_color(peak_color),
    m_start({ 0, window_height / 2 }), m_end({ window_width, window_height / 2 }) {}


void PeakTrackerLayer::draw(SDL_Renderer * const renderer, const wave & signal) {
    int wave_amplitude = m_window_height / 4;
    draw_wave(renderer, signal, m_start, m_end, wave_amplitude, m_color);
    auto peak_positions = m_peaks.get_peak_positions(signal);
    for (const auto& peak_pos : peak_positions) {
        SDL_Point point = point_on_line(m_start, m_end, peak_pos);
        draw_circle(renderer, point, 20, m_color);
    }
}