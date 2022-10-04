#include "screen_box_layer.h"

#include "../Utilities/draw_utilities.h"

void ScreenBoxLayer::draw(SDL_Renderer * const renderer, const wave & signal) {
    scale += scale_rate;
    if (scale <= 0.0) {
        return;
    }

    SDL_Point centre{ window_width / 2, window_height / 2 };
    SDL_Point tl = { int((1.0 - scale) * double(centre.x)), int((1.0 - scale) * double(centre.y)) };
    SDL_Point tr = { (window_width - 1) - int((1.0 - scale) * double(centre.x)), int((1.0 - scale) * double(centre.y)) };
    SDL_Point bl = { int((1.0 - scale) * double(centre.x)) , (window_height - 1) - int((1.0 - scale) * double(centre.y)) };
    SDL_Point br = { (window_width - 1) - int((1.0 - scale) * double(centre.x)) , (window_height - 1) - int((1.0 - scale) * double(centre.y)) };

    for (int i = wave_count; i >= 0; --i) {
        int wave_amplitude = (i == 0 ? 0 : int(amplitude * i / wave_count));
        // use width/height - 1 so the stationary line is visible
        draw_wave(renderer, signal, tl, bl, -wave_amplitude, color);
        draw_wave(renderer, signal, bl, br, -wave_amplitude, color);
        draw_wave(renderer, signal, br, tr, -wave_amplitude, color);
        draw_wave(renderer, signal, tr, tl, -wave_amplitude, color);
    }
}
