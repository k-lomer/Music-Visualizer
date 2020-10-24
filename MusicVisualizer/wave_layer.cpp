#include "wave_layer.h"

#include "draw_utilities.h"

void WaveLayer::draw(SDL_Renderer * const renderer, const SignalBox & signal_box) {
    auto wave = signal_box.gen_wave(signal_type);
    
    for (int i = wave_count; i > 0; --i) {
        int wave_amplitude = int(amplitude * scale * i / wave_count);
        draw_wave(renderer, wave, start, end, wave_amplitude, color);
    }
}
