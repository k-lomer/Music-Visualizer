#include "moving_wave_layer.h"

#include <algorithm>

#include "draw_utilities.h"

MovingWaveLayer::MovingWaveLayer(int num_waves, orientation wave_orientation, double wave_movement, int width, int height, int wave_amplitude, SDL_Color wave_color)
    : wave_orientation(wave_orientation), movement(wave_movement), window_width(width), window_height(height), amplitude(wave_amplitude), color(wave_color) {
    // we use num_waves + 1 for a smooth transition on/off screen
    for (int i = 0; i < num_waves + 1; ++i) {
        int length = wave_orientation == Horizontal ? height : width;
            wave_positions.push_back(double(length) * double(i) / double(num_waves) + double(length) / (2 * double(num_waves)));
    }
}

// this is made trickier than it should be to ensure a smooth transition (wraparound) between waves
// there is always an extra wave that only becomes visible as the previous one leaves the screen
void MovingWaveLayer::draw(SDL_Renderer * renderer, const SignalBox & signal_box) {
    int length = wave_orientation == Horizontal ? window_height : window_width;
    int visible_waves = (int)wave_positions.size() - 1;
    // move wave positions and wrap around waves which are off the screen
    for (double & pos : wave_positions) {
        pos += movement;
        if (movement > 0 && pos > length + length / visible_waves) {
            pos -= length + length / visible_waves;
        }
        else if (movement < 0 && pos < -length / visible_waves) {
            pos += length + length / visible_waves;
        }
    }

    auto wave = signal_box.gen_wave(signal_type);

    for (double pos : wave_positions) {
        if (wave_orientation == Horizontal) {
            draw_wave(renderer, wave, SDL_Point{0, int(pos)}, SDL_Point{window_width, int(pos) }, amplitude, color);
        }
        else {
            draw_wave(renderer, wave, SDL_Point{ int(pos), 0}, SDL_Point{ int(pos), window_height }, amplitude, color);
        }
    }

}
