#include "wave_layer.h"

#include "draw_utilities.h"

void WaveLayer::draw(SDL_Renderer * const renderer, const packet & packet_buffer) {
    for (int i = wave_count; i > 0; --i) {
        int wave_amplitude = int(amplitude * scale * i / wave_count);
        draw_wave(renderer, packet_buffer, start, end, wave_amplitude, color);
    }
}
