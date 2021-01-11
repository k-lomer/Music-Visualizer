#include "unknown_pleasure_layer.h"

#include "draw_utilities.h"

void UnknownPleasureLayer::draw(SDL_Renderer * renderer, const SignalBox & signal_box) {
    waveforms.push_front(signal_box.gen_wave(signal_type));
    waveforms.pop_back();

    auto starts = interpolate_line(front_start, back_start, wave_count);
    auto ends = interpolate_line(front_end, back_end, wave_count);
    for (int i = 0; i < starts.size(); ++i) {
        draw_wave(renderer, waveforms[i], starts[i], ends[i], amplitude, color);
    }
}
