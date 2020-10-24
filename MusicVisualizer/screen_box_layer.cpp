#include "screen_box_layer.h"

#include "draw_utilities.h"

void ScreenBoxLayer::draw(SDL_Renderer * const renderer, const SignalBox & signal_box) {
    int wave_amplitude = int(amplitude * scale);
    auto wave = signal_box.gen_wave(signal_type);
    // use width/height - 1 so the stationary line is visible
    draw_wave(renderer, wave, SDL_Point{ 0, 0 }, SDL_Point{ 0, window_height - 1}, -wave_amplitude, color);
    draw_wave(renderer, wave, SDL_Point{ 0, 0 }, SDL_Point{ window_width - 1, 0}, wave_amplitude, color);
    draw_wave(renderer, wave, SDL_Point{ 0, window_height - 1}, SDL_Point{ window_width - 1, window_height - 1}, -wave_amplitude, color);
    draw_wave(renderer, wave, SDL_Point{ window_width - 1, 0 }, SDL_Point{ window_width - 1, window_height - 1}, wave_amplitude, color);
}
