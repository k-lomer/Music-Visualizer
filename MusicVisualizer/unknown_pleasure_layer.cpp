#include "unknown_pleasure_layer.h"

#include "draw_utilities.h"

UnknownPleasureLayer::UnknownPleasureLayer(int num_waves, int frame_delay, SDL_Point first_wave_start, SDL_Point first_wave_end,
    SDL_Point last_wave_start, SDL_Point last_wave_end, int wave_amplitude, SDL_Color wave_color)
    : wave_count(num_waves), delay(frame_delay), front_start(first_wave_start), front_end(first_wave_end),
    back_start(last_wave_start), back_end(last_wave_end), amplitude(wave_amplitude), color(wave_color)
{
    for (int i = 0; i < wave_count * delay + 1; ++i) {
        waveforms.emplace_back();
    }
}

void UnknownPleasureLayer::draw(SDL_Renderer * renderer, const SignalBox & signal_box) {
    waveforms.push_front(signal_box.gen_wave(signal_type));
    waveforms.pop_back();

    auto starts = interpolate_line(front_start, back_start, wave_count);
    auto ends = interpolate_line(front_end, back_end, wave_count);
    for (int i = 0; i < starts.size(); ++i) {
        draw_wave(renderer, waveforms[i * delay], starts[i], ends[i], amplitude, color);
    }
}
