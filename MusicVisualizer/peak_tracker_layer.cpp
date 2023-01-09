#include "peak_tracker_layer.h"

#include "../Utilities/draw_utilities.h"

PeakTrackerLayer::PeakTrackerLayer(int num_peaks, int window_width, int window_height, SDL_Color peak_color)
    : peaks(num_peaks), window_width(window_width), window_height(window_height), color(peak_color),
    start({ 0, window_height / 2 }), end({ window_width, window_height / 2 }) {}


void PeakTrackerLayer::draw(SDL_Renderer * const renderer, const wave & signal) {
    int wave_amplitude = window_height / 4;
    draw_wave(renderer, signal, start, end, wave_amplitude, color);
    auto peak_positions = peaks.get_peak_positions(signal);
    for (const auto& peak_pos : peak_positions) {
        SDL_Point point = point_on_line(start, end, peak_pos);
        draw_circle(renderer, point, 20, color);
    }
}