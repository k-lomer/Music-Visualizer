#include "screen_box_layer.h"

#include "draw_utilities.h"

void ScreenBoxLayer::draw(SDL_Renderer * const renderer, const SignalBox & signal_box) {
    auto wave = signal_box.gen_wave(signal_type, 0.2);
    for (int i = wave_count; i > 0; --i) {
        int wave_amplitude = int(amplitude * i / wave_count);
        // use width/height - 1 so the stationary line is visible
        draw_wave(renderer, wave, SDL_Point{ 0, 0 }, SDL_Point{ 0, window_height - 1 }, -wave_amplitude, color);
        draw_wave(renderer, wave, SDL_Point{ 0, 0 }, SDL_Point{ window_width - 1, 0 }, wave_amplitude, color);
        draw_wave(renderer, wave, SDL_Point{ 0, window_height - 1 }, SDL_Point{ window_width - 1, window_height - 1 }, -wave_amplitude, color);
        draw_wave(renderer, wave, SDL_Point{ window_width - 1, 0 }, SDL_Point{ window_width - 1, window_height - 1 }, wave_amplitude, color);
    }
}
