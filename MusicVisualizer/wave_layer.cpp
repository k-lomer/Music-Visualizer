#include "wave_layer.h"

#include "../Utilities/draw_utilities.h"

void WaveLayer::draw(SDL_Renderer * const renderer, const wave & signal) {
    rotation += rotation_rate;
    if (rotation > 2 * M_PI) {
        rotation -= 2 * M_PI;
    }
    else if (rotation < 0.0) {
        rotation += 2 * M_PI;
    }
    
    SDL_Point rotated_start = rotate_point(start, centre, rotation);
    SDL_Point rotated_end = rotate_point(end, centre, rotation);

    for (int i = wave_count; i > 0; --i) {
        int wave_amplitude = int(amplitude * i / wave_count);
        draw_wave(renderer, signal, rotated_start, rotated_end, wave_amplitude, color);
    }
    for (int i = wave_count; i > 0; --i) {
        int wave_amplitude = -int(amplitude * i / wave_count);
        draw_wave(renderer, signal, rotated_start, rotated_end, wave_amplitude, color);
    }
}
